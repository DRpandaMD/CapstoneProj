#!/bin/bash

# Removes all data files
rm /home/pi/Documents/Shutters_Scripts/temp/*_temp >/dev/null
rm /home/pi/Documents/Shutters_Scripts/light/*_light >/dev/null

# Create data files
touch /home/pi/Documents/Shutters_Scripts/temp/{1..8}_temp
touch /home/pi/Documents/Shutters_Scripts/light/{1..8}_light
echo "To search for a date type '/dd-mm-yyyy<enter>'" | tee \
	/home/pi/Documents/Shutters_Scripts/temp/{1..8}_temp \
	/home/pi/Documents/Shutters_Scripts/light/{1..8}_light >/dev/null
