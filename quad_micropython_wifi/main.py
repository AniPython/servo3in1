from quad import Quad
from robot_wifi import RobotWifi

ifconfig = ("192.168.2.182", "255.255.255.0", "192.168.2.1", "8.8.8.8")

robot = Quad()
robot.init(12, 16, 25, 18, 13, 17, 26, 19)
robot.setTrims(0, 0, 0, 0, 0,0,0, 0)

robot_wifi = RobotWifi(robot=robot)

# AP模式
# dog_wifi.create_connect_ap(essid="OttoDiyWifi", password="88889999", ifconfig=ifconfig)

# 路由模式
robot_wifi.create_connect_route(ssid='小亦站', password='88889999', ifconfig=ifconfig)

robot_wifi.create_server()


