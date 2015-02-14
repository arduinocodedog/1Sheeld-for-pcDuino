/*

  Project:       1Sheeld Library 
  File:          SMSShield.cpp
                 
  Version:       1.0

  Compiler:      Arduino avr-gcc 4.3.2

  Author:        Integreight
                 
  Date:          2014.5

*/

#include "OneSheeld.h"
#include "SMSShield.h"

//Class Constructor
 SMSShieldClass::SMSShieldClass()
  {
  	text=0;
  	number=0;
  	isCallBackAssigned=false;
  	isItNewSms=false;
  	usedSetOnWithString=false;
  }
//SMS Sender
void SMSShieldClass::send(const char* number,const char* text)
{
	OneSheeld.sendPacket(SMS_ID,0,SMS_SEND,2,new FunctionArg(strlen(number),(byte*)number),new FunctionArg(strlen(text),(byte*)text));
}

bool SMSShieldClass::isNewSms()
{
	return isItNewSms;
}
//Support string for Arduino 
#if !defined(ARDUINO_LINUX)
void SMSShieldClass::send(String number ,String text)
{
	const char * cTypeNumber = number.c_str();
	const char * cTypeText = text.c_str();

	send(cTypeNumber,cTypeText);
}
#endif
//Support string for galileo
#if defined(ARDUINO_LINUX)
void SMSShieldClass::send(String number,String text)
{
	int numberLength = number.length();
	int textLength = text.length();

	char cTypeNumber[numberLength+1];
	char cTypeText[textLength+1];

	for (int i = 0; i < numberLength; i++)
	{
		cTypeNumber[i]=number[i];
	}
	cTypeNumber[numberLength]='\0';

	for (int j = 0; j <textLength; j++)
	{
		cTypeText[j]=text[j];
	}
	cTypeText[textLength]='\0';

	send(cTypeNumber,cTypeText);
}
#endif

//Number Getter
char * SMSShieldClass::getNumber()
{
	isItNewSms=false;
	return number;
}
//Number Getter
String SMSShieldClass::getNumberAsString()
{
	isItNewSms=false;
	String numberInString (number);
	return numberInString;
}
//SMS Getter
char * SMSShieldClass::getSms()
{
	isItNewSms=false;
	return text;
}
//SMS Getter
String SMSShieldClass::getSmsAsString()
{
	isItNewSms=false;
	String smsInString(text);
	return smsInString;
}

//SMS Input Data Processing
void SMSShieldClass::processData()
  {
  	//Checking Function-ID
	byte x= OneSheeld.getFunctionId();
	if(x==SMS_GET)
	{
		isItNewSms =true;
		if(text!=0)
		{
			free(text);
		}
		if (number!=0)
		{
			free(number);
		}
		int numberlength=OneSheeld.getArgumentLength(0);
		number=(char*)malloc(sizeof(char)*(numberlength+1));
		for (int j=0; j<numberlength; j++)
		{
			number[j]=OneSheeld.getArgumentData(0)[j];
		}
		number[numberlength]='\0';
		int textlength=OneSheeld.getArgumentLength(1);
		text=(char*)malloc(sizeof(char)*(textlength+1));

		for(int i=0 ;i<textlength;i++)
		{
			text[i]=OneSheeld.getArgumentData(1)[i];
		}
			text[textlength]='\0';
		//Users Function Invoked
		if(isCallBackAssigned)
		{
			(*changeCallBack)(number,text);
		}

		if(usedSetOnWithString)
		{
			(*changeCallBackString)(getNumberAsString(),getSmsAsString());
		}
	}
}
//Users Function Setter
void SMSShieldClass::setOnSmsReceive(void (*userFunction)(char * number ,char * text))
{
	changeCallBack=userFunction;
	isCallBackAssigned=true;
}

void SMSShieldClass::setOnSmsReceive(void (*userFunction)(String number ,String text))
{
	changeCallBackString=userFunction;
	usedSetOnWithString=true;
}


//Instantiating Object
SMSShieldClass SMS;