from otto9 import Otto9
from robot_wifi import RobotWifi

ifconfig = ("192.168.3.182", "255.255.255.0", "192.168.3.1", "8.8.8.8")

robot = Otto9(servo_totals=4)
robot.init(YL=25, YR=18, RL=26, RR=19)
robot.setTrims(0, 0, 0, 0)

robot_wifi = RobotWifi(robot=robot)

# AP模式
# dog_wifi.create_connect_ap(essid="OttoDiyWifi", password="88889999", ifconfig=ifconfig)

# 路由模式
robot_wifi.create_connect_route(ssid='Yi', password='88889999', ifconfig=ifconfig)

robot_wifi.create_server()
