import machine
import usocket as socket
import network
import time
import json


class TrimsWifi:
    def __init__(self, html_path='trims.html'):
        with open(html_path, 'r', encoding='utf-8') as file:
            self.html = file.read()

    def create_connect_ap(self, essid, password, ifconfig=None):
        ap = network.WLAN(network.AP_IF)
        if ifconfig:
            ap.ifconfig(ifconfig)
        ap.active(True)
        ap.config(essid=essid, password=password)
        print('Access Point created!')
        machine.PWM(machine.Pin(2), duty=512)
        ip = ap.ifconfig()[0]
        print("ip:", ip)
        return ip

    def create_connect_route(self, ssid, password, ifconfig=None):
        wlan = network.WLAN(network.STA_IF)
        if ifconfig:
            wlan.ifconfig(ifconfig)
        wlan.active(True)
        if not wlan.isconnected():
            print('connecting to network...')
            wlan.connect(ssid, password)
            i = 1
            while not wlan.isconnected():
                print("正在链接...{}".format(i))
                i += 1
                time.sleep(1)
        ip = wlan.ifconfig()[0]
        machine.PWM(machine.Pin(2), duty=512)
        print("ip:", ip)
        return ip
    
    def set_angle(self, pin, angle):
        duty = int(angle * 102 / 180 + 26)
        machine.PWM(machine.Pin(pin), freq=50, duty=duty)

    def handle_post_request(self, post_data):
        try:
            pin = json.loads(post_data).get("pin")
            angle = json.loads(post_data).get("angle")
            self.set_angle(int(pin), int(angle))
            return 'OK'
        except Exception as e:
            print("Error:", str(e))
            return 'Error'

    def handle_get_request(self):
        response_headers = 'HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n'
        return response_headers + self.html

    def handle_request(self, client_socket):
        request = b''
        while b'\r\n\r\n' not in request:
            chunk = client_socket.recv(1024)
            if not chunk:
                break
            request += chunk

        request_str = request.decode('utf-8')
        request_lines = request_str.split('\r\n')
        method, path, _ = request_lines[0].split()

        if method == "GET":
            response = self.handle_get_request()
        elif method == "POST" and path == "/control":
            post_data = request_lines[-1]
            response = self.handle_post_request(post_data)
        else:
            response = "unknow"

        client_socket.send(response.encode('utf-8'))
        client_socket.close()

    def create_server(self):
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server_socket.bind(('', 80))
        server_socket.listen(5)
        print('HTTP server started!')

        while True:
            client_socket, addr = server_socket.accept()
            self.handle_request(client_socket)


if __name__ == '__main__':
    ifconfig = ("192.168.3.180", "255.255.255.0", "192.168.3.1", "8.8.8.8")

    trims = TrimsWifi()

    # AP模式
    # trims.create_connect_ap(essid="OttoDiyWifi", password="88889999", ifconfig=ifconfig)

    # 路由模式
    trims.create_connect_route(ssid='Yi', password='88889999', ifconfig=ifconfig)

    trims.create_server()
