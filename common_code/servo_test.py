
from machine import Pin, PWM
from time import sleep


def set_servo_angle(pin, angle):
    duty = int(angle * 102 / 180 + 26)
    PWM(Pin(pin), freq=50, duty=duty)
    sleep(0.5)


pin_list = [13, 12, 14, 27]


for pin in pin_list:
    set_servo_angle(pin, 60)
    set_servo_angle(pin, 120)
    set_servo_angle(pin, 90)
