import time
import socket
from machine import Pin, I2C, Timer
from micropython_mma8451 import mma8451
import network

nic=network.WLAN(network.STA_IF)
nic.active(True)

nic.connect('', '')


while not nic.isconnected():
    print("Waiting")
    time.sleep(5)
    
print("Connected")
ipaddr=nic.ifconfig()[0]



diode_yneg=13
diode_xneg=15
diode_ypoz=14
diode_xpoz=12

yneg=Pin(diode_yneg, Pin.OUT)
xneg=Pin(diode_xneg, Pin.OUT)
ypoz=Pin(diode_ypoz, Pin.OUT)
xpoz=Pin(diode_xpoz, Pin.OUT)

i2c=I2C(scl=5, sda=4, freq=100000)
mma = mma8451.MMA8451(i2c, 28)

timer=Timer(1)
sock=socket.socket()
addr=socket.getaddrinfo('ip', 0)[0][-1]
sock.connect(addr)

def mjerenje(a):
    x, y, z = mma.acceleration
    #print(f"Acceleration: X={x:0.1f}m/s^2 y={y:0.1f}m/s^2 z={z:0.1f}m/s^2")
    #print()
    xpoz.off()
    xneg.off()
    ypoz.off()
    yneg.off()
    if x>1.0:
        xpoz.on()
    if x<-1.0:
        xneg.on()
    if y>1.0:
        ypoz.on()
    if y<-1.0:
        yneg.on()
    sock.send(f'{x:0.3f} {y:0.3f} {z:0.3f}\n')


timer.init(period=20, mode=Timer.PERIODIC, callback=mjerenje)

