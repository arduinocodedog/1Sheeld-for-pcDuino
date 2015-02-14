/*

Magnetometer Shield Example

This example shows an application on 1Sheeld's magnetometer shield.

By using this example, you can send a SMS when the magnetic
field strength read by the smartphone's magnetometer exceeds
a certain value.

*/

/* Include 1Sheeld library*/
#include <OneSheeld.h>

/* Define a boolean flag. */
boolean isPhoneNotified = false;
/* A name for a LED on pin 13. */
int ledPin = 13;

void setup()
{
  /* Start communication. */
  OneSheeld.begin();
  /* Set the LED pin as output. */
  pinMode(ledPin,HIGH);
}

void loop() 
{
  
  /* Check if the magnetic strength exceeded a certain value. */
  if (MagnetometerSensor.getMagneticStrength() > 50)
  {
      /* This makes sure that the SMS will be sent only one time. */ 
      if (!isPhoneNotified)
      {
        /* Send the SMS. */
        SMS.send("1234567890","Danger: Magnetic field increased checkout what's the problem.");
        /* Turn on the LED. */
        digitalWrite(ledPin,HIGH);
        /* Reset the flag. */
        isPhoneNotified = true;
      }
  }
  else
  {
    /* Set the flag. */
    isPhoneNotified = false ;
    /* Turn off the LED. */
    digitalWrite(ledPin,LOW);
  }
  
}
