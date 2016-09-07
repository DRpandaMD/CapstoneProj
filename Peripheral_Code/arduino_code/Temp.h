#ifndef Temp_h
#define Temp_h

#include "Arduino.h"

// Returns the current Fahrenheit reading
float get_temp_reading(int sensorPin);

// Used to debug on monitor output
void debug_temp();

#endif
