/*

  Project:       1Sheeld Library 
  File:          GamePadShield.cpp
                 
  Version:       1.0

  Compiler:      Arduino avr-gcc 4.3.2

  Author:        Integreight
                 
  Date:          2014.5

*/

#include "OneSheeld.h"
#include "GamePadShield.h"



//Class Constructor
GamePadShield::GamePadShield()
{
	isCallBackAssigned=false;
}

//Up ArrowChecker
bool GamePadShield::isUpPressed()
{
	return up ;
}
//Down Arrow Checker 
bool GamePadShield::isDownPressed()
{
	return down ;
}
//Left Arrow Checker
bool GamePadShield::isLeftPressed()
{
	return left ;
}
//Right Arrow Checker
bool GamePadShield::isRightPressed()
{
	return right ;
}
//Orange Button Checker
bool GamePadShield::isOrangePressed()
{
	return orange ;
}
//Red Button Checker 
bool GamePadShield::isRedPressed()
{
	return red ;
}
//Green Button Checker 
bool GamePadShield::isGreenPressed()
{
	return green ;
}
//Blue Button Checker
bool GamePadShield::isBluePressed()
{
	return blue ;
}
//GamePad Input Data Processing  
void GamePadShield::processData()
{
	//Checking Function-ID
	byte functionId =OneSheeld.getFunctionId();
	if(functionId==GAMEPAD_VALUE)
	{
		byte value=OneSheeld.getArgumentData(0)[0];
		
		up = !!(value & (1<<UP_BIT));
		down = !!(value & (1<<DOWN_BIT));
		left = !!(value & (1<<LEFT_BIT));
		right = !!(value & (1<<RIGHT_BIT));
		orange = !!(value & (1<<ORANGE_BIT));
		red = !!(value & (1<<RED_BIT));
		green = !!(value & (1<<GREEN_BIT));
		blue = !!(value & (1<<BLUE_BIT));

		//Users Function Invoked
		if(isCallBackAssigned)
		{
			(*buttonChangeCallBack)(up , down , left , right , orange , red , green , blue);
		}
	}
}

//Users Function Setter 
void GamePadShield::setOnButtonChange(void (* userFunction)(unsigned char up,unsigned char down,unsigned char left,unsigned char right,unsigned char orange ,unsigned char red,unsigned char green,unsigned char blue))
{
	buttonChangeCallBack=userFunction;
	isCallBackAssigned=true;
}

//Instantiating Object
GamePadShield GamePad;