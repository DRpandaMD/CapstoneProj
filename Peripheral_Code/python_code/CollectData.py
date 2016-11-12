# Collects data from various Arduino modules. Parses the data and stores it in appropriate files
import serial

ser = serial.Serial('/dev/ttyUSB0', 9600)

# Forever loop to grab incoming data
while True:
	# Need to figure out way to set times at which the modules can transmit data
	incoming = ser.read(8)
	print "%s" % incoming

	# parse the data
	moduleID = incoming[0]
	temp = incoming[1:4]
	light = incoming[4:7]
	
	print "id:%s, temp:%s, light:%s" % (moduleID, temp, light)

	# Open and write to data file
	dataFile = open("/home/pi/Documents/Shutter_Project/sensor_data/module_%s" % moduleID, 'a') # abs path of data file
	dataFile.write(temp + "F\t" + light + " lumens\n")
	
	dataFile.close()
