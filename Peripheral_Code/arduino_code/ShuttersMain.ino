#include <SoftwareSerial.h>
#include "Temp.h"
#include "Light.h"
#include "Servo.h"

Servo motor;
bool servo_state;
int tempSensorPin = 0; // Required by the function that gets the temp reading
int power = 1; // state of module; 1 for ON and 0 for OFF
int inputData; // stores the input from any incoming broadcasts

void setup() {
  Serial.begin(9600);
  light_setup();
  motor.attach(9, 1000, 2000); // digital pin 9, 1000/2000 min/max PWM limits
}

void loop() {
  /**************************************
  ***** React to manual inputs here *****
  **************************************/ 
  /* Steps:
  * - check ID of incoming serial data, since all modules will broadcast their data; react only if sent from ID 0 (RPi) 
  * - format will be <ID><1 or 0 for ON/OFF><000000> where the zeros are fillers -- ex. 01000000
  * - set the power variable depending on what was sent by the RPi; power variable tells the Arduino 
  *   to continue or halt its operation
  * ************************************
  * The data being broadcasted by the sender is in the form of "1" and "0" characters. 
  * The Serial.read() command below interprets the 1 and 0 chars as the equivalent decimal ascii value. 
  * Therefore we must compose an 8 char string from the ascii values received.
  */
  if(servo_state)
    {
      motor.write(180);
      servo_state = false;
    }
    else
    {
      motor.write(0);
      servo_state = true;
     }
  
  while (Serial.available()) {
    String command = "";

    // Constructs the 8 character string data
    for (int i=0; i<8; i++) {
      inputData = Serial.read(); // Reads any incoming data
      command += (char)inputData; // appends the char representation from the ascii value received
    }
    
    Serial.print("Data received: ");
    Serial.println(command);
    
    // check whether the received broadcast is from RPi or other modules. If from other modules, then ignore
    if (command[0] == '0') {
      Serial.println("Data was sent from RPi");
      if (command[1] == '1') power = 1;
      else power = 0;
    }
    else Serial.println("Data was sent from another Arduino\nData will be ignored");
  }
  
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
  }
  
  // Sleep 5 seconds
  delay(5000);
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
