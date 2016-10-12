#ifndef Temp_h
#define Temp_h

#include "Arduino.h"

// Gets a single temperature reading in Fahrenheit
float get_temp_reading(int sensorPin);

// Returns the current average of 10 temperature readings
float get_clustered_temp_reading(int sensorPin);

// Used to debug on monitor output
void debug_temp();

#endif
