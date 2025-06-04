import serial
import time
import requests
import threading
import os

# === CONFIGURAÇÃO SERIAL E HTTP ===
COM_PORT = 'COM3'          # Altere para sua porta
BAUD_RATE = 115200

LOGIN_ENDPOINT       = "http://localhost:8080/auth/login"
SEND_ENDPOINT        = "http://localhost:8080/measurements"
RELAY_STATE_ENDPOINT = "http://localhost:8080/relay/state"

UUID_USER = "a63f809e-f9a2-462d-a5c5-5fe1a6482a10"

payload = {
    "email": "Kaique@gmail.com",
    "password": "123456"
}

# === COMANDOS AT FIXOS ===
FIXED_COMMANDS = {
    "AT":           "OK",
    "AT+INIT":      "OK",
    "AT+SEND":      "OK",
    "AT+SETUPWIFI": "OK",
    "AT+RESET":     "OK",
}

# === COMANDOS COM VALOR (ex.: AT+VEFICAZ=valor) ===
ARG_COMMANDS = {
    "AT+VEFICAZ=":   "vEficaz",
    "AT+IEFICAZ=":   "iEficaz",
    "AT+PAPARENTE=": "pAparente",
    "AT+PATIVA=":    "pAtiva",
    "AT+PREATIVA=":  "pReativa",
    "AT+FP=":        "fatorPotencia"
}

# Estrutura para armazenar valores lidos
values = {
    "vEficaz":       0.0,
    "iEficaz":       0.0,
    "pAparente":     0.0,
    "pAtiva":        0.0,
    "pReativa":      0.0,
    "fatorPotencia": 0.0
}

# Mutex para sincronizar acesso à porta serial
serial_lock = threading.Lock()

# Evento para sinalizar recebimento de "OK" referente a comando de relé
relay_ok_event = threading.Event()

def parse_command(cmd: str) -> str:
    """
    Analisa um comando AT (string sem quebras de linha) e retorna
    a resposta apropriada: "OK" ou "NO", ou repassa comandos AT+DATA_*.
    """
    cmd = cmd.strip().replace('\r', '').replace('\n', '')
    if cmd.startswith("AT+DATA"):
        # Indica que virão linhas "AT+DATA_<campo>=<valor>"
        return cmd

    if cmd in FIXED_COMMANDS:
        return FIXED_COMMANDS[cmd]

    for prefix, field in ARG_COMMANDS.items():
        if cmd.startswith(prefix):
            try:
                value = float(cmd[len(prefix):])
                values[field] = value
                return "OK"
            except:
                return "NO"

    return "NO"

def relay_poller(ser, headers):
    """
    Thread que faz polling de /relay/state a cada 1 segundo.
    Se detectar mudança (0 ↔ 1), envia AT+RELE_ON ou AT+RELE_OFF
    repetidamente até receber "OK" do ESP. Usa relay_ok_event para
    saber quando o OK chegou, e serial_lock para escrever na serial.
    """
    relay_last_state = None

    while True:
        try:
            resp = requests.get(RELAY_STATE_ENDPOINT, headers=headers, timeout=2)
            if resp.status_code == 200:
                novo_estado = resp.json().get("relay")
                if relay_last_state is None:
                    relay_last_state = novo_estado
                elif novo_estado != relay_last_state:
                    relay_last_state = novo_estado

                    if novo_estado == 1:
                        cmd_rele = "AT+RELE_ON"
                    else:
                        cmd_rele = "AT+RELE_OFF"

                    print(f"[Relay Poller] Estado do relé mudou para {novo_estado}. Tentando enviar comando: {cmd_rele}")

                    # Limpa evento e tenta enviar até receber OK
                    relay_ok_event.clear()
                    while True:
                        with serial_lock:
                            ser.write((cmd_rele + "\r\n").encode())
                        # Espera até 0.5s por um set() no relay_ok_event
                        ok_received = relay_ok_event.wait(timeout=0.5)
                        if ok_received:
                            print(f"[Relay Poller] OK recebido para {cmd_rele}")
                            break
                        else:
                            print(f"[Relay Poller] Sem OK ainda, reenviando {cmd_rele}")
            else:
                print(f"[Relay Poller] Erro ao consultar /relay/state: {resp.status_code}")
        except Exception as e:
            print(f"[Relay Poller] Exceção ao fazer GET /relay/state: {e}")

        time.sleep(1.0)  # espera 1 segundo antes da próxima consulta

def serial_reader(ser, headers):
    """
    Thread que lê continuamente da porta serial.
    - Se recebe "OK" e relay_ok_event não estiver setado, sinaliza relay_ok_event.
    - Se recebe "AT+SEND", responde "OK" para permitir o ESP enviar AT+DATA.
    - Se recebe "AT+DATA_*", coleta 6 linhas, atualiza 'values' e faz POST em /measurements.
    - Para outros ATs, usa parse_command() e responde OK ou NO.
    """
    while True:
        if ser.in_waiting:
            raw = ser.readline().decode(errors='ignore').strip()

            # 1) SE RECEBEU "OK" DO MÓDULO ESP: sinaliza relay_ok_event (se estiver aguardando)
            if raw == "OK":
                # Define evento indicando que o ESP respondeu OK a um AT+RELE_*
                if not relay_ok_event.is_set():
                    relay_ok_event.set()
                    print("[Serial Reader] “OK” recebido do ESP → sinal relay_ok_event.set()")
                # Não envia resposta de volta ao ESP; este "OK" é só confirmação de comando
                continue

            # 2) COMANDO AT+SEND: ACK IMEDIATO PARA ESP
            if raw == "AT+SEND":
                print(f"[Serial Reader] Recebido do ESP: AT+SEND → Respondendo OK")
                with serial_lock:
                    ser.write("OK\r\n".encode())
                continue

            # 3) INÍCIO DOS DADOS: AT+DATA_<campo>=<valor>
            if raw.startswith("AT+DATA_"):
                try:
                    keys = list(values.keys())  # ['vEficaz', 'iEficaz', ..., 'fatorPotencia']
                    # Já recebemos a primeira linha em 'raw'; ler mais 5
                    for i in range(6):
                        if i == 0:
                            data_line = raw
                        else:
                            data_line = ser.readline().decode(errors='ignore').strip()

                        print(f"[Serial Reader] Linha recebida: {data_line}")
                        parts = data_line.split('=')
                        if len(parts) == 2:
                            valor_recebido = float(parts[1])
                            values[keys[i]] = valor_recebido
                        else:
                            print(f"[Serial Reader] Formato inválido em: {data_line}")

                    print("\n[Serial Reader] Valores atualizados:")
                    for key, val in values.items():
                        print(f"    {key}: {val}")

                    # Envia para o servidor de medições
                    print("\n[Serial Reader] Enviando dados para o servidor...")
                    json_payload = {
                        "v_eficaz":       values["vEficaz"],
                        "i_eficaz":       values["iEficaz"],
                        "p_aparente":     values["pAparente"],
                        "p_ativa":        values["pAtiva"],
                        "p_reativa":      values["pReativa"],
                        "fator_potencia": values["fatorPotencia"],
                        "user_id":        UUID_USER
                    }
                    try:
                        r = requests.post(SEND_ENDPOINT, json=json_payload, headers=headers, timeout=5)
                        print(f"[Serial Reader] [POST] Status: {r.status_code} - {r.text}")
                    except Exception as e:
                        print(f"[Serial Reader] [POST] Erro ao enviar: {e}")

                    # Confirma ao ESP que processamos todos os dados
                    with serial_lock:
                        ser.write("OK\r\n".encode())

                except Exception as e:
                    print(f"[Serial Reader] Erro no processamento dos valores: {e}")

            # 4) QUALQUER OUTRO COMANDO AT: parse e responde OK ou NO
            else:
                print(f"[Serial Reader] Recebido do ESP: {raw}")
                resposta = parse_command(raw)
                with serial_lock:
                    ser.write((resposta + "\r\n").encode())
                print(f"[Serial Reader] Resposta enviada ao ESP: {resposta}")

        else:
            time.sleep(0.01)  # evita loop 100% ocupado

def simulate_esp():
    # 1) Faz login na API
    try:
        response = requests.post(LOGIN_ENDPOINT, json=payload, timeout=5)
        if response.status_code == 200:
            token = response.json().get("token")
            print("Login realizado com sucesso.")
        else:
            print("Falha no login:", response.text)
            return
    except Exception as e:
        print("Erro de login:", e)
        return

    headers = {"Authorization": f"Bearer {token}"}

    # 2) Abre a porta serial
    try:
        ser = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)
        print(f"Simulador AT em {COM_PORT} @ {BAUD_RATE}")
    except serial.SerialException as e:
        print(f"Erro serial: {e}")
        return

    # 3) Inicia threads de polling e de leitura serial
    try:
        t_relay = threading.Thread(target=relay_poller, args=(ser, headers), daemon=True)
        t_serial = threading.Thread(target=serial_reader, args=(ser, headers), daemon=True)

        t_relay.start()
        t_serial.start()

        # Mantém a thread principal viva até Ctrl+C
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nSimulador encerrado.")
        ser.close()
        os._exit(0)

if __name__ == "__main__":
    simulate_esp()
