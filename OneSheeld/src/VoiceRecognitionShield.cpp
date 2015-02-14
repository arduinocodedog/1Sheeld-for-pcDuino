/*

  Project:       1Sheeld Library 
  File:          VoiceRecognitionShield.cpp
                 
  Version:       1.2

  Compiler:      Arduino avr-gcc 4.3.2

  Author:        Integreight
                 
  Date:          2014.9

*/
#include "OneSheeld.h"
#include "VoiceRecognitionShield.h"


//Constructor 
VoiceRecognitionShield::VoiceRecognitionShield()
{
	voice =0;
	voicetextLength=-1;
	isCallBackAssigned=false;
	newCommand=false;
	errorAssigned=false;
	didDataCame=false;
	usedSetOnWithString=false;
	errorNumber='\0';
}
//Start Listen the voice command  
void VoiceRecognitionShield::start()
{
	OneSheeld.sendPacket(VOICE_RECOGNITION_ID,0,VOICE_START_LISTENING,0);
}
//Get and save the voice command
char * VoiceRecognitionShield::getLastCommand()
{
	newCommand=false;
	return voice;
}
//Get length of last voice command
int VoiceRecognitionShield::getLastCommandLength()
{
	return voicetextLength;
} 
//Check if new voice command received
bool VoiceRecognitionShield::isNewCommandReceived()
{
	return newCommand;
}
String VoiceRecognitionShield::getCommandAsString()
{
		String dataInString (voice);
		return dataInString;
}

//Process Input Data
void VoiceRecognitionShield::processData()
{
	byte functionID = OneSheeld.getFunctionId();

	if(functionID==VOICE_GET)
	{
		if (voice!=0)
		{
			free(voice);
		}
		
		voicetextLength=OneSheeld.getArgumentLength(0);
		voice = (char*)malloc(sizeof(char)*(voicetextLength+1));
		for (int j=0; j<voicetextLength; j++)
		{
			voice[j]=OneSheeld.getArgumentData(0)[j];
		}
		voice[voicetextLength]='\0';

		
		newCommand=true;

		//Invoke Users function
		if(isCallBackAssigned)
		{
			(*changeCallBack)(voice);
		}
		//Invoke Users function
		if (usedSetOnWithString)
		{
			String convertedIncomingVoice (voice);

			(*changeCallBackString)(convertedIncomingVoice);
		}

	}
	else if(functionID==VOICE_GET_ERROR)
	{
		errorNumber=OneSheeld.getArgumentData(0)[0];
		//Invoke User Function
		if(errorAssigned)
		{
			(*errorCallBack)(errorNumber);
		}
	}
}
//Users Function Setter 
void VoiceRecognitionShield::setOnNewCommand(void (*userFunction)(char * voice))
{
	changeCallBack=userFunction;
	isCallBackAssigned=true;
}

//Users Function Setter return String data 
void VoiceRecognitionShield::setOnNewCommand(void (*userFunction)(String voice))
{
	changeCallBackString=userFunction;
	usedSetOnWithString=true;
}

void VoiceRecognitionShield::setOnError(void (*userFunction)(byte error))
{
	errorCallBack=userFunction;
	errorAssigned=true;
}
//Instantiating object 
VoiceRecognitionShield VoiceRecognition;