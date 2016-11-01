#include "Light.h"


TSL2561 tsl(TSL2561_ADDR_FLOAT);

void light_setup() {
	// Attempts to power-up and connect sensor
	if (tsl.begin()) {
		Serial.println("Found Sensor");
	} 
	else {
		Serial.println("No Sensor?");
		while(1);
	}

	// Sets the sensitivity and the integration
	// time for the sensor.
	// Integration time is the amount of time the sensor
	// stays "on" to read the lux
	tsl.setGain(TSL2561_GAIN_0X);
	tsl.setTiming(TSL2561_INTEGRATIONTIME_13MS);
}

float get_light_reading() {
	// Does stuff I don't understand yet
	uint32_t lum = tsl.getFullLuminosity();
	uint16_t ir, full;
	ir = lum >> 16;
	full = lum & 0xFFFF;

	return tsl.calculateLux(full, ir);
}

float get_clustered_light_reading() {
	float total = 0.0;

	// Collects 10 readings and adds them to total
	for (unsigned int i=0; i<10; i++) {
		total += get_light_reading();
		delay(250); // Waits a quarter second between readings
	}

	return total/10; // returns the average
}
