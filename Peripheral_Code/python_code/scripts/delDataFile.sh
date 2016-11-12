#!/bin/bash

# Removes all data files
rm /home/pi/Documents/Shutter_Project/sensor_data/module_* >/dev/null 2>&1 || true

# Create new data files
touch /home/pi/Documents/Shutter_Project/sensor_data/module_{1..6}

# Adds search directions and column names to data files
echo "To search for a data, type '/dd-mm-yyyy<enter>'" | tee \
    /home/pi/Documents/Shutter_Project/sensor_data/module_{1..6} >/dev/null
