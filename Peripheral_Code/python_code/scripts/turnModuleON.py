# Sends a signal to the Arduino's to turn on

import serial

ser = serial.Serial('/dev/ttyUSB0', 9600)
ser.write("01000000")
