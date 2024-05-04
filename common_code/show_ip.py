import network
import machine
import time

# WiFi 名称和密码
ssid = "Yi"
password = "88889999"

# 连接 WiFi
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)

# 等待连接成功
while not wlan.isconnected():
    print("Connecting...")
    time.sleep(1)

# 显示 ESP32 的 IP 地址
ip = wlan.ifconfig()[0]
print("IP:", ip)

# 启动一个 PWM 输出，可以用于控制 LED 亮度等
pwm = machine.PWM(machine.Pin(2), duty=512)
