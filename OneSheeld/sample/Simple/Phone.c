/*

Phone Shield Example

This example shows an application on 1Sheeld's phone shield.

By using this example, you can call someone from your
smartphone each time you press the hardware push button
placed on pin 12.

OPTIONAL:
To reduce the library compiled size and limit its memory usage, you
can specify which shields you want to include in your sketch by
defining CUSTOM_SETTINGS and the shields respective INCLUDE_ define. 

*/

#define CUSTOM_SETTINGS
#define INCLUDE_PHONE_SHIELD

/* Include 1Sheeld library. */
#include <OneSheeld.h>

/* A name for the button on pin 12. */
int buttonPin = 12;
/* A name for the LED on pin 13. */
int ledPin = 13;

void setup() 
{
  /* Start communication. */
  OneSheeld.begin();
  /* Set the button pin as input. */
  pinMode(buttonPin,INPUT);
  /* Set the LED pin as output. */
  pinMode(ledPin,OUTPUT);
}

void loop()
{
  /* Always check the button state. */
  if(digitalRead(buttonPin) == HIGH)
  {
      /* Turn on the LED. */
      digitalWrite(ledPin,HIGH);
      /* Call a friend. */
      Phone.call("1234567890");
      /* Wait for 300 ms. */
      OneSheeld.delay(300);
  }

  /* Turn off the LED. */
  digitalWrite(ledPin,LOW);
}
