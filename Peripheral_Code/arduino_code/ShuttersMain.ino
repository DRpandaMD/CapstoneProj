#include <SoftwareSerial.h>
#include "Temp.h"
#include "Light.h"

int tempSensorPin = 0; // Required by the function that gets the temp reading
//SoftwareSerial XBee(0, 1); // RX, TX
int power = 1; // state of module; 1 for ON and 0 for OFF

void setup() {
  Serial.begin(9600); 
  //XBee.begin(9600); // Not too sure what this is doing
  light_setup();  
}

void loop() {
  /***********************************
  ***** Check for manual inputs *****
  ***********************************/ 
  /*while (Serial.available()) {
    Serial.print("Stuff came in\n");
    Serial.print(Serial.read());
    Serial.print("\n");
  }*/

  while (Serial.available()) {
    Serial.println(Serial.read()); // Reads any incoming data from RPi
  }
  /**************************************
  ***** React to manual inputs here *****
  **************************************/ 
  /* Steps:
   * - check id of incoming serial data as all modules will broadcast their info; react only if sent from id 0 (RPi) 
   * - format will be <id><1/0 (Power ON/OFF)>
   * - set power variable equal to incoming data
   */
   
   
  /**********************************
  ***** Get light/temp readings *****
  **********************************/
  if (power) // checks whether operation has been suspended by manual input
  {
    // Converted to integers to keep the XBee transmission simple
    int tempReading = (int)get_clustered_temp_reading(tempSensorPin);
    int lightReading = (int)get_clustered_light_reading();
    
    // Creates data string in the appropriate format for transmission to RPi
    String outputData = format_data("1", tempReading, lightReading);
    
    // Prints data to serial monitor which causes a broadcast to all XBee devices
    Serial.print(outputData);
    
    // Found code that used the XBee.command() format but I'm
    // not sure what it does, since Serial.command() already 
    // takes care of broadcasting the data
    //XBee.write(tempReading);
    //XBee.write(lightReading);
    //XBee.println("5 seconds have passed");
  
    // Sleep 5 seconds
    delay(5000);
  }
}

// Formats the data into a compact transmission string
// format: <id><3char temp reading><3 char light reading>
// ex: 1100400, where the starting 1 is the id, 100 is the temp reading, and 400 is the lux reading
String format_data(String moduleID, int tempReading, int lightReading) {
  String data = moduleID;
  char reading[3];
  sprintf(reading, "%03d", tempReading);
  data += reading;
  sprintf(reading, "%03d", lightReading);
  data += reading; 
  data += "\n";
  return data;
}
