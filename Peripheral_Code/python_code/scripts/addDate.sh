#!/bin/bash
echo $(date +"%d-%m-%Y") | tee /home/pi/Documents/Shutters_Scripts/temp/{1..6}_temp >/dev/null
echo $(date +"%d-%m-%Y") | tee /home/pi/Documents/Shutters_Scripts/light/{1..6}_light >/dev/null
