#ifndef Light_h
#define Light_h

#include "Arduino.h"
#include "TSL2561.h"
#include <Wire.h>


void light_setup();
float get_light_reading();

#endif
