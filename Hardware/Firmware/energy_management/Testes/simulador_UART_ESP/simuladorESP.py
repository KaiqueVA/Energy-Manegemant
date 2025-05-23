import serial
import time
import requests
import os
import time

# === CONFIGURAÇÃO SERIAL E HTTP ===
COM_PORT = 'COM3'          # Altere para sua porta
BAUD_RATE = 115200
LOGIN_ENDPOINT = "http://localhost:8080/auth/login"
SEND_ENDPOINT = "http://localhost:8080/measurements"

UUID_USER = "a63f809e-f9a2-462d-a5c5-5fe1a6482a10"

payload = {
    "email": "Kaique@gmail.com",
    "password": "123456"
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

COMMANDS_TO_STM = {
    "AT+RELE_ON": "OK",
    "AT+RELE_OFF": "OK",
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
    token = None
    # try:
    #     response = requests.post(LOGIN_ENDPOINT, json=payload)
    #     if response.status_code == 200:
    #         token = response.json().get("token")
    #         print("Login realizado com sucesso.")
    #         print("Token:", token)
    #     else:
    #         print("Falha no login:", response.text)
    #         return
    # except Exception as e:
    #     print("Erro de login:", e)
    #     return
        

    
    
    try:
        with serial.Serial(COM_PORT, BAUD_RATE, timeout=1) as ser:
            print(f"Simulador AT em {COM_PORT} @ {BAUD_RATE}")
            last_time_trigger = time.time()
            value = False 
            response_command_stm = ""
            
            while True:
                current_time = time.time()
                if current_time - last_time_trigger >= 10:
                    print(f"Comando enviado: {'AT+RELE_ON' if value else 'AT+RELE_OFF'}")
                    if value == True:
                        response_command_stm = "AT+RELE_ON"
                        value = False
                    else:
                        response_command_stm = "AT+RELE_OFF"
                        value = True

                    ser.write((response_command_stm + "\r\n").encode())
                    while not esperar_ok(ser, 0.25):
                        ser.write((response_command_stm + "\r\n").encode())
                        
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
                            # if token:
                            #     print("\nEnviando dados para o servidor...")
                            #     json_payload = {
                            #         "v_eficaz": values["vEficaz"],
                            #         "i_eficaz": values["iEficaz"],
                            #         "p_aparente": values["pAparente"],
                            #         "p_ativa": values["pAtiva"],
                            #         "p_reativa": values["pReativa"],
                            #         "fator_potencia": values["fatorPotencia"],
                            #         "user_id": UUID_USER
                            #     }

                            #     headers = {
                            #         "Authorization": f"Bearer {token}"
                            #     }

                            #     try:
                            #         r = requests.post(SEND_ENDPOINT, json=json_payload, headers=headers)
                            #         print(f"\n[POST] Status: {r.status_code} - {r.text}")
                            #     except Exception as e:
                            #         print(f"[POST] Erro ao enviar: {e}")
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
