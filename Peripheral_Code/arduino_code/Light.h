#ifndef Light_h
#define Light_h

#include "Arduino.h"
#include "TSL2561.h"
#include <Wire.h>

// Configures light sensor for immediate use
void light_setup();

// Returns a single light reading in lux
float get_light_reading();

// Returns the current average of 10 light readings
float get_clustered_light_reading();

#endif
