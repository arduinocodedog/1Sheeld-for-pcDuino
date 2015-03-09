/*

  Project:       1Sheeld Library 
  File:          PressureSensorShield.cpp
                 
  Version:       1.0

  Compiler:      Arduino avr-gcc 4.3.2

  Author:        Integreight
                 
  Date:          2014.5

*/
#include "OneSheeld.h"
#include "PressureSensorShield.h"

//Class Constructor
PressureSensorShield::PressureSensorShield() : ShieldParent(PRESSURE_ID)
{
	value=0;
	isCallBackAssigned=false;
}
//Pressure Getter
unsigned long PressureSensorShield::getValue()
{
	
	return value;
	
}

//PressureSensor Input Data Processing 
void PressureSensorShield::processData()
{
	//Checking Function-ID
	byte functionId =getOneSheeldInstance().getFunctionId();
	if(functionId==PRESSURE_VALUE)
	{
		value=0;
		data[0]=getOneSheeldInstance().getArgumentData(0)[0];
		data[1]=getOneSheeldInstance().getArgumentData(0)[1];
		value|=data[0];
		value|=(data[1]<<8);
		//Users Function Invoked
		if(isCallBackAssigned && !isInACallback())
		{
			enteringACallback();
			(*changeCallBack)(value);
			exitingACallback();
		}
	}
}
//Users Function Setter
void PressureSensorShield::setOnValueChange(void (*userFunction)(unsigned long pressureValue))
{
	changeCallBack=userFunction;
	isCallBackAssigned=true;
}

#ifdef PRESSURE_SHIELD
//Instatntiating Object
PressureSensorShield PressureSensor;
#endif