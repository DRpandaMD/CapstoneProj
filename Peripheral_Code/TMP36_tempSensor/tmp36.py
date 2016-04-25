import RPi.GPIO as GPIO
import json
import time
import readadc
import datetime

# temperature sensor middle pin connected channel 0 of mcp3008
sensor_pin = 0
readadc.initialize()

# We initialize the LED GPIO pins
redPin = 17
greenPin = 4
GPIO.setup(redPin, GPIO.OUT)
GPIO.setup(greenPin, GPIO.OUT)

#the main sensor reading and plotting loop
while True:
    sensor_data = readadc.readadc(sensor_pin,
                                  readadc.PINS.SPICLK,
                                  readadc.PINS.SPIMOSI,
                                  readadc.PINS.SPIMISO,
                                  readadc.PINS.SPICS)

    millivolts = sensor_data * (3300.0 / 1024.0)
    # 10 mv per degree
    temp_C = ((millivolts - 100.0) / 10.0) - 40.0
    # convert celsius to fahrenheit
    temp_F = (temp_C * 9.0 / 5.0) + 32
    # remove decimal point from millivolts
    millivolts = "%d" % millivolts
    # show only one decimal place for temperature and voltage readings
    temp_F = "%.1f\n" % temp_F
    print "TempF: %s" % temp_F,

    # We check whether to turn on the red or green LED. If temp<80
    # then green else red
    if float(temp_F) < 80.0:
        GPIO.output(redPin, 0)
        GPIO.output(greenPin, 1)
    else:
        GPIO.output(greenPin, 0)
        GPIO.output(redPin, 1)

    # We write the data to tmp_output.txt to be sent over TCP
    with open("tmp_output.txt", "a") as textfile:
        textfile.write(temp_F)
    
    # delay between readings
    time.sleep(1)
