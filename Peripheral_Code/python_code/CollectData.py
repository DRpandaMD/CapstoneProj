# Collects data from various Arduino modules. Parses the data and stores it in appropriate files

import serial

ser = serial.Serial('/dev/ttyUSB0', 9600)

# Forever loop to grab incoming data
while True:
	incoming = ser.read(8)
	print "%s" % incoming

	# parse the data
	moduleID = incoming[0]
	temp = incoming[1:4]
	light = incoming[4:]
	
	print "id:%s, temp:%s, light:%s" % (moduleID, temp, light)

	# store data in corresponding files
	tempFile = open("/home/pi/Documents/Shutters_Scripts/temp/%s_temp" % moduleID, 'a') # absolute path of temperature file
	lightFile = open("/home/pi/Documents/Shutters_Scripts/light/%s_light" % moduleID, 'a')  # absolute path of light file
	
	tempFile.write(temp + "\n")
	lightFile.write(light)
	
	tempFile.close()
	lightFile.close()
