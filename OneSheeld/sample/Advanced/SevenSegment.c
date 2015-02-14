/*

Seven Segment Shield Example

This example shows an application on 1Sheeld's seven segment shield.

By using this example, you can display the numbers from
0 till 9 on the app's seven segment every time you press
the button on pin 12.

*/

/* Include 1Sheeld library. */
#include <OneSheeld.h>

/* Define a variable to hold the seven segment digit. */
int number = 0;
/* A name for the button on pin 12. */
int buttonPin = 12;

void setup() 
{
  /* Start communication. */
  OneSheeld.begin();
  /* Set the button pin as input. */
  pinMode(buttonPin,INPUT);
}

void loop() 
{
  if (digitalRead(buttonPin) == HIGH)
  {
    /* Display the number on the seven segment. */
    SevenSegment.setNumber(number);
    /* Wait for a second. */
    delay(1000);
    /* Increment the number. */
    number++;
    /* If the number reaches 9, return it back to zero. */
    if(number > 9)
    {
      number = 0;
    }
  }
}
