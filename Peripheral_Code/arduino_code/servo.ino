/******************************************************************************
servo-skatch.ino
Example sketch for connecting a hobby servo to a sparkfun redboard
  (https://www.sparkfun.com/products/9065)
  (https://www.sparkfun.com/products/12757)
Byron Jacquot@ SparkFun Electronics
May 17, 2016

**SparkFun code, firmware, and software is released under the MIT License(http://opensource.org/licenses/MIT).**

Development environment specifics:
Arduino 1.6.5
******************************************************************************/

#include <Servo.h>

Servo myservo;

uint32_t next;
bool state;
void setup()
{
  // the 1000 & 2000 set the pulse width 
  // mix & max limits, in microseconds.
  // Be careful with shorter or longer pulses.
  myservo.attach(9, 1000, 2000);
  //digital 9 pin on arduino
}

void loop()
{
  if(state)
    {
      myservo.write(180);
      state = false;
    }
    else
    {
      myservo.write(0);
      state = true;
      
    }
  }

