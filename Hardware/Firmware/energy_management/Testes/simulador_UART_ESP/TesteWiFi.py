import network
import socket
import ure

# Função para escanear redes Wi-Fi disponíveis
def scan_networks():
    sta_if = network.WLAN(network.STA_IF)
    if not sta_if.active():
        sta_if.active(True)
    nets = sta_if.scan()
    # nets é lista de tuplas (ssid, bssid, channel, RSSI, authmode, hidden)
    ssids = [net[0].decode('utf-8') for net in nets]
    return ssids

# Página HTML com o form dinâmico para redes disponíveis
def web_page(ssids):
    options = ""
    for ssid in ssids:
        options += '<option value="{}">{}</option>'.format(ssid, ssid)
    html = """<!DOCTYPE html>
    <html>
    <head><title>Configurar Wi-Fi</title></head>
    <body>
    <h2>Configuração Wi-Fi</h2>
    <form action="/connect" method="POST">
        <label>Selecione a rede:</label><br>
        <select name="ssid">{}</select><br><br>
        <label>Senha:</label><br>
        <input type="password" name="password"><br><br>
        <input type="submit" value="Conectar">
    </form>
    </body>
    </html>""".format(options)
    return html

# Configura o AP para o ESP servir a página
ap = network.WLAN(network.AP_IF)
ap.active(True)
ap.config(essid='ESP_Config')

addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]

s = socket.socket()
s.bind(addr)
s.listen(1)

print('Servidor rodando em http://{}'.format(addr))

while True:
    cl, addr = s.accept()
    print('Cliente conectado de', addr)
    cl_file = cl.makefile('rwb', 0)
    request_line = cl_file.readline()
    print('Request:', request_line)
    
    # Lê cabeçalhos até linha vazia
    while True:
        line = cl_file.readline()
        if not line or line == b'\r\n':
            break
    
    if request_line.startswith(b'POST /connect'):
        length = 0
        # Pega dados do POST (pode precisar melhorar essa parte)
        content_length = 0
        # Tenta pegar content length para ler body (simplificado)
        # aqui assumimos corpo no formato: ssid=Nome&password=Senha
        # Leia body:
        body = cl_file.read()
        body_str = body.decode('utf-8')
        
        # Parse simples do corpo
        import ure
        params = {}
        for pair in body_str.split('&'):
            k,v = pair.split('=')
            params[k] = ure.unquote_plus(v)
        
        ssid = params.get('ssid')
        password = params.get('password')
        
        # Tenta conectar ao Wi-Fi usando a SSID e senha
        sta_if = network.WLAN(network.STA_IF)
        sta_if.active(True)
        sta_if.connect(ssid, password)
        
        # Espera conexão (com timeout simplificado)
        import time
        timeout = 10
        while timeout > 0:
            if sta_if.isconnected():
                break
            time.sleep(1)
            timeout -= 1
        
        if sta_if.isconnected():
            response = """<h2>✅ Conectado ao Wi-Fi</h2><p>SSID: {}</p>""".format(ssid)
        else:
            response = "<h2>❌ Falha na conexão</h2><p>Tente novamente</p>"
        
        cl.send('HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n')
        cl.send(response)
        cl.close()
    else:
        # Serve a página principal com o form e SSIDs
        ssids = scan_networks()
        response = web_page(ssids)
        cl.send('HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n')
        cl.send(response)
        cl.close()
