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

shutters_open = False
previous_reading = "open"
# tracks the number of consecutive points of the opposite state
consecutive_counter = 0

# collects temp data
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
    # then green(shutters_open) else red(!shutters_open)
    if float(temp_F) < 81.2:
        GPIO.output(redPin, 0)
        GPIO.output(greenPin, 1)
        if shutters_open == False and previous_reading == "open":
            consecutive_counter += 1
            #print "Up went counter"
        elif consecutive_counter > 34 and previous_reading == "open":
            continue
        else:
            #print "Counter reset"
            consecutive_counter = 0
        #print "Counter is: ", str(consecutive_counter)
        previous_reading = "open"
            
            
    else:
        GPIO.output(greenPin, 0)
        GPIO.output(redPin, 1)
        if shutters_open and previous_reading == "close":
            consecutive_counter += 1
            #print "Up went counter"
        elif consecutive_counter > 34 and previous_reading == "close":
            continue
        else:
            consecutive_counter = 0
            #print "Counter reset"
        #print "Counter is: ", str(consecutive_counter)
        previous_reading = "close"

    # We write the data to tmp_output.txt to be sent over TCP
    with open("/home/pi/sensor-readings/tmp_output.txt", "a") as textfile:
        textfile.write(temp_F)
    
    # If there have been 36 data points urging to change the state of 
    # the shutters, then we change the state and reset the counter.
    # The first data point isn't counted, therefore we go up to 35
    if consecutive_counter == 35:
        print "Shutters changed state"
        shutters_open = ~shutters_open
        consecutive_counter = 0
    
    # delay between readings
    time.sleep(3)
