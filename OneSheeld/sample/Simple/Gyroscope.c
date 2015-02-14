/*

Gyroscope Shield Example

This example shows an application on 1Sheeld's gyroscope shield.

By using this example, you can turn on some LEDs if the
smartphone's gyroscope sensor moves in any of the x, y
and z axises.

*/

/* Include 1Sheeld library. */
#include <OneSheeld.h>

/* A name for the LED on pin 13. */
int ledPin1 = 13;
/* A name for the LED on pin 12. */
int ledPin2 = 12;
/* A name for the LED on pin 11. */
int ledPin3 = 11;

void setup()
{
  /* Start communication. */
  OneSheeld.begin();
  /* Set LEDs 1, 2 and 3 as output. */
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
}

void loop() 
{
  /* Check X-axis motion value. */
  if(GyroscopeSensor.getX() > 1)
  {
    /* Turn on the LED 1. */
    digitalWrite(ledPin1,HIGH);
    /* Turn off the other LEDs. */
    digitalWrite(ledPin2,LOW);
    digitalWrite(ledPin3,LOW); ;
  }

  /* Check Y-axis motion value. */
  if(GyroscopeSensor.getY() > 1)
  {
    /* Turn on the LED 2. */
    digitalWrite(ledPin2,HIGH);
    /* Turn off the other LEDs. */
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin3,LOW);  
  } 

  /* Check Z-axis motion value. */
  if(GyroscopeSensor.getZ() > 1)
  {
    /* Turn on the LED 3. */
    digitalWrite(ledPin3,HIGH);
    /* Turn off the other LEDs. */
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin2,LOW); 
  }
}
