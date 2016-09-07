#include "Temp.h"
#include "Light.h"

int tempSensorPin = 0; // Required by the function that gets the temp reading

void setup() {
  Serial.begin(9600); 
  light_setup();  
}

void loop() {
  /************************************
  ***** Check for manual commands *****
  ************************************/ 


  /**********************************
  ***** Get light/temp readings *****
  **********************************/
  float tempReading = get_temp_reading(tempSensorPin);
  float lightReading = get_light_reading();

  // Print temp/light data to monitor
  Serial.print(tempReading); Serial.println(" degrees Fahrenheit");
  Serial.print(lightReading); Serial.println(" lux");

  // Sleep 5 seconds
  delay(5000);
}
