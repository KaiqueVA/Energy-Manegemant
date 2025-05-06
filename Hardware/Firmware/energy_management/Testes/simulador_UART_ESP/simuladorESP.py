import serial
import time
import requests
import os
import time

# === CONFIGURAÇÃO SERIAL E HTTP ===
COM_PORT = 'COM3'          # Altere para sua porta
BAUD_RATE = 115200
LOGIN_ENDPOINT = "http://192.168.15.157:8080/auth/login"
SEND_ENDPOINT = ""

payload = {
    "email": "lelezinho@email.com",
    "password": "266468"
}


# === COMANDOS AT FIXOS ===
FIXED_COMMANDS = {
    "AT": "OK",
    "AT+INIT": "OK",
    "AT+SEND": "OK",
    "AT+SETUPWIFI": "OK",
    "AT+RESET": "OK",
}

FIXED_COMMANDS_ESP = {
    "AT+RELE_ON": "OK",
    "AT+RELE_OFF": "OK",
}

# === COMANDOS COM VALOR ===
ARG_COMMANDS = {
    "AT+VEFICAZ=": "vEficaz",
    "AT+IEFICAZ=": "iEficaz",
    "AT+PAPARENTE=": "pAparente",
    "AT+PATIVA=": "pAtiva",
    "AT+PREATIVA=": "pReativa",
    "AT+FP=": "fatorPotencia"
}

values = {
    "vEficaz": 0.0,
    "iEficaz": 0.0,
    "pAparente": 0.0,
    "pAtiva": 0.0,
    "pReativa": 0.0,
    "fatorPotencia": 0.0
}

# === PARSE DE COMANDOS ===
def parse_command(cmd):
    cmd = cmd.strip().replace('\r', '').replace('\n', '')
    if cmd.startswith("AT+DATA"):
        return cmd
    
    if cmd in FIXED_COMMANDS:
        return FIXED_COMMANDS[cmd]
    for prefix, field in ARG_COMMANDS.items():
        if cmd.startswith(prefix):
            try:
                value = float(cmd[len(prefix):])
                energia_data[field] = value
                return "OK"
            except:
                return "NO"

    return "NO"


def esperar_ok(ser, timeout=2):
    
    start_time = time.time()
    while True:
        if ser.in_waiting:
            data = ser.readline().decode(errors='ignore').strip()
            print(f"Resposta do ESP: {data}")
            if data == "OK":
                print("Recebido OK, continuando...")
                return True  
        if time.time() - start_time > timeout:
            print("Timeout esperando OK!")
            return False  
    

# === LOOP PRINCIPAL ===
def simulate_esp():
    # try:
    #     response = requests.post(LOGIN_ENDPOINT, json=payload)
    #     if response.status_code == 200:
    #         print("Login realizado com sucesso!")
    #         print("Token ou resposta:", response.json())
    #     else:
    #         print(f"Erro ao fazer login: {response.status_code}")
    #         print(response.text)
    
    # except requests.exceptions.RequestException as e:
    #     print(f"Erro na requisição: {e}")
        

    last_time_trigger = time.time()
    value = False
    try:
        with serial.Serial(COM_PORT, BAUD_RATE, timeout=1) as ser:
            print(f"Simulador AT em {COM_PORT} @ {BAUD_RATE}")
            while True:
                current_time = time.time()
                if current_time - last_time_trigger >= 30:
                    print(f"Comando enviado: {'AT+RELE_ON' if value else 'AT+RELE_OFF'}")
                    if value == True:
                        ser.write(('AT+RELE_ON' + "\r\n").encode())
                        value = False
                    else:
                        value = True
                        ser.write(('AT+RELE_OFF' + "\r\n").encode())
                    esperar_ok(ser, 2)
                    last_time_trigger = current_time
                    
                if ser.in_waiting:
                    data = ser.readline().decode(errors='ignore')
                    response = parse_command(data)
                    if response.startswith("AT+DATA_"):
                        try:
                            keys = list(values.keys())  # ['vEficaz', 'iEficaz', ..., 'fatorPotencia']
                            for i in range(6):
                                if i == 0:
                                    data_line = data.strip()
                                else:
                                    data_line = ser.readline().decode(errors='ignore').strip()

                                print(f"Linha recebida: {data_line}")

                                # Agora corretamente alinhado
                                parts = data_line.split('=')
                                if len(parts) == 2:
                                    valor_recebido = float(parts[1])
                                    values[keys[i]] = valor_recebido
                                else:
                                    print(f"Formato inválido em: {data_line}")

                            print("\nValores atualizados:")
                            for key, val in values.items():
                                print(f"    {key}: {val}")

                            #ser.write(("OK\r\n").encode())

                        except Exception as e:
                            print(f"Erro no processamento dos valores: {e}")
                    else:
                        print(f"{data.strip()}")
                        time.sleep(0.1)
                        ser.write((response + "\r\n        ").encode())
                        print(f"{response}")
    except serial.SerialException as e:
        print(f"Erro serial: {e}")
    except KeyboardInterrupt:
        os.system('cls')
        print("\nSimulador encerrado.")

if __name__ == "__main__":
    simulate_esp()
