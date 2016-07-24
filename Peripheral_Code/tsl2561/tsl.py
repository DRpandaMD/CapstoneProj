from Adafruit_I2C import Adafruit_I2C
import time

address = 0x39
i2c = Adafruit_I2C(address)
control_on = 0x03
control_off = 0x00

def enable():
    # print "enabling"
    i2c.write8(0x80, control_on)

def disable():
    # print "disabling"
    i2c.write(0x80, control_off)

def getLight():
    x = i2c.readU8(0xAE)
    x <<= 16
    x |= i2c.readU8(0xAC)
    return x

# collects luminosity data
while True:
    enable()
    
    # Gets the current light value
    light = getLight()
    #print light

    # We write the data to tsl_output.txt to be sent over TCP
    with open("/home/pi/sensor-readings/tsl_output.txt", "a") as textfile:
        textfile.write(str(light)+"\n")

    # Delay between readings
    time.sleep(5)
    
