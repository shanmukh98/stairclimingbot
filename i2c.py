import smbus
import time
bus=smbus.SMBus(1)
address=[0x04,0x05,0x06,0x07]
while True:
    speed=input('Enter speed 0-31\n')
    direction=input('Enter direction\n 3-forward\n 0-backward\n 1-right\n 2-left\n')
    instruction=speed+(direction<<5)
    for i in address:
        bus.write_byte(i,instruction)
        print i
        time.sleep(0.01)

