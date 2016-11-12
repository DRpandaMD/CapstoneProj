#!/bin/bash

# Removes all data files
rm /home/pi/Documents/Shutters_Scripts/temp/*_temp >/dev/null
rm /home/pi/Documents/Shutters_Scripts/light/*_light >/dev/null

# Create data files
touch /home/pi/Documents/Shutters_Scripts/temp/{1..6}_temp
touch /home/pi/Documents/Shutters_Scripts/light/{1..6}_light

# Adds search directions to light and temp files
echo "To search for a date type '/dd-mm-yyyy<enter>'" | tee \
	/home/pi/Documents/Shutters_Scripts/temp/{1..6}_temp \
	/home/pi/Documents/Shutters_Scripts/light/{1..6}_light >/dev/null
