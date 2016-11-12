#!/bin/bash

echo $(date +"%d-%m-%Y") | tee -a /home/pi/Documents/Shutter_Project/sensor_data/module_{1..6} >/dev/null
