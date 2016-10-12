#!/bin/bash
echo $(date +"%d-%m-%Y") | tee /home/pi/Documents/Shutters_Scripts/temp/[0-8]_temp >/dev/null
echo $(date +"%d-%m-%Y") | tee /home/pi/Documents/Shutters_Scripts/light/[0-8]_light >/dev/null
