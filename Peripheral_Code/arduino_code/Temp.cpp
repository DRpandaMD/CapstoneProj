#include "Temp.h"


float get_temp_reading(int sensorPin) {
	// Gets the reading from the tmp sensor
	int reading = analogRead(sensorPin);	

	// Converts the reading to voltage
	// For 3.3V ref use 3.3 instead of 5.0
	float voltage = reading * 5.0;
	voltage /= 1024.0;

	// Gets the temperature in Celsuis
	// Converts from 10mv per degree to degrees times 100
	float tempC = (voltage - 0.5) * 100;

	// Converts the temperature to Fahrenheit
	float tempF = (tempC * 9.0 / 5.0) + 32.0;

	return tempF;
}

float get_clustered_temp_reading(int sensorPin) {
	float total = 0.0;

	// Collects 10 readings and adds them to total
	for (unsigned int i=0; i<10; i++) {
		total += get_temp_reading(sensorPin);
		delay(500); // Waits half a second between readings
	}

	return total/10; // returns the average
}

void debug_temp() {
	Serial.println("Check");
}
