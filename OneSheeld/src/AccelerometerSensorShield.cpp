/*

  Project:       1Sheeld Library 
  File:          AccelerometerSensorShield.cpp
                 
  Version:       1.0

  Compiler:      Arduino avr-gcc 4.3.2

  Author:        Integreight
                 
  Date:          2014.5

*/
#include "OneSheeld.h"
#include "AccelerometerSensorShield.h"



//Class Constructor
AccelerometerSensorShield::AccelerometerSensorShield(): ShieldParent(ACCELEROMETER_ID)			 
{
	valueX=0;
	valueY=0;
	valueZ=0;
	isCallBackAssigned=false;
}

//X-Axis getter function
float AccelerometerSensorShield::getX()							 
{
	return valueX;
}

//Y-Axis getter function
float AccelerometerSensorShield::getY()							
{
	return valueY;
}

//Z-Axis getter function
float AccelerometerSensorShield::getZ()							
{
	return valueZ;
}

//AccelerometerSensor Input Data processing 	
void AccelerometerSensorShield::processData()					
{
	//Check Function-ID
	byte functionId=OneSheeld.getFunctionId();
	
		if(functionId==ACCELEROMETER_VALUE)
		{
			//Process X-Axis Value
			valueX=OneSheeld.convertBytesToFloat(getOneSheeldInstance().getArgumentData(0));
			//Process Y-Axis Value
			valueY=OneSheeld.convertBytesToFloat(getOneSheeldInstance().getArgumentData(1));
			//Process Z-Axis Value
			valueZ=OneSheeld.convertBytesToFloat(getOneSheeldInstance().getArgumentData(2));
			
			//User Function Invoked
			if(isCallBackAssigned && !isInACallback())
			{
				enteringACallback();
				(*changeCallBack)(valueX,valueY,valueZ);
				exitingACallback();
			}
		}	
}

//Users Function Setter 
void AccelerometerSensorShield::setOnValueChange(void (* usersFunction)(float valueX,float valueY,float valueZ))	
{
	changeCallBack=usersFunction;
	isCallBackAssigned=true;
}

#ifdef ACCELEROMETER_SHIELD
//Instatntiating Object
AccelerometerSensorShield AccelerometerSensor;					
#endif