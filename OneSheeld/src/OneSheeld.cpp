/*

  Project:       1Sheeld Library 
  File:          OneSheeld.cpp
                 
  Version:       1.2

  Compiler:      Arduino avr-gcc 4.3.2

  Author:        Integreight
                 
  Date:          2014.5

*/
  
#include "OneSheeld.h"
#if defined(PCDUINO)
#include "Serial.h"
#else
#include "HardwareSerial.h"
#endif
#include "stdarg.h"

//Shields ID's
byte inputShieldsList[]={ONESHEELD_ID
,KEYPAD_SHIELD_ID
,GPS_ID
,SLIDER_ID
,PUSH_BUTTON_ID
,TOGGLE_BUTTON_ID
,GAMEPAD_ID
,PROXIMITY_ID
,MIC_ID
,TEMPERATURE_ID
,LIGHT_ID
,PRESSURE_ID
,GRAVITY_ID
,ACCELEROMETER_ID
,GYROSCOPE_ID
,ORIENTATION_ID
,MAGNETOMETER_ID
,PHONE_ID
,SMS_ID
,CLOCK_ID
,KEYBOARD_ID
,TWITTER_ID
,VOICE_RECOGNITION_ID,
TERMINAL_ID,
REMOTE_SHEELD_ID,
};


//Class Constructor
OneSheeldClass::OneSheeldClass(Stream &s) :OneSheeldSerial(s)
{
      shield=0;
      instance=0;
      functions=0;
      counter=0;
      argumentcounter=0;
      datalengthcounter=0;
      argumentnumber=0;
      endFrame=0;
      lastTimeFrameSent=0;
      numberOfDataMalloced=0;
      remoteOneSheeldsCounter=0;
      isFirstFrame=false;
      isArgumentsNumberMalloced=false;
      isArgumentLengthMalloced=false;
      usedSetOnFloatWithString=false;
      usedSetOnStringWithString=false;
      isOneSheeldRemoteDataUsed=false;
}

//Library Starter
void OneSheeldClass::begin(long baudRate)
{
  #if defined(__AVR_ATmega32U4__) || (defined(ARDUINO_LINUX) && !defined(PCDUINO))
  Serial1.begin(baudRate);
  #else
  Serial.begin(baudRate);
  #endif
}
//Blocking function 
void OneSheeldClass::waitForAppConnection()
{
  isOneSheeldConnected = false;

  while(!isOneSheeldConnected)
  {
    OneSheeld.processInput();
  }

}
//Library Starter
void OneSheeldClass::begin()
{
  begin(115200);
}

//Frame Sender for Output Shields
void OneSheeldClass::sendPacket(byte shieldID, byte instanceID, byte functionID, byte argNo, ...)
{
  unsigned long mill=millis()+1;
 if(shieldID!=ONESHEELD_ID&&isFirstFrame&&lastTimeFrameSent&&(mill-lastTimeFrameSent)<TIME_GAP) 
    delay(TIME_GAP-(mill-lastTimeFrameSent));
  isFirstFrame=true;
  va_list arguments ;
  va_start (arguments,argNo);
  OneSheeldSerial.write((byte)START_OF_FRAME);
  OneSheeldSerial.write(LIBRARY_VERSION);
  OneSheeldSerial.write(shieldID);
  OneSheeldSerial.write(instanceID);
  OneSheeldSerial.write(functionID);
  OneSheeldSerial.write(argNo);
  OneSheeldSerial.write(255-argNo);


  for (int i=0 ; i<argNo ; i++)
  {
    FunctionArg * temp = va_arg(arguments, FunctionArg *);
    OneSheeldSerial.write(temp->getLength());
    OneSheeldSerial.write(255-(temp->getLength()));

      for (int j=0 ; j<temp->getLength() ; j++)
      {
        byte* tempData=temp->getData();
        OneSheeldSerial.write(tempData[j]);
      }
    delete(temp);

 }
    OneSheeldSerial.write((byte)END_OF_FRAME);
    va_end(arguments);
    lastTimeFrameSent=millis()+1;
}
bool OneSheeldClass::isAppConnected()
{
  return isOneSheeldConnected;
}
//Shield_ID Getter
byte OneSheeldClass::getShieldId()
{
  return shield;
} 
//Instance_ID Getter
byte OneSheeldClass::getInstanceId()
{
  return instance;
} 
//Funtcion_ID Getter
byte OneSheeldClass::getFunctionId()
{
  return functions;
}
//ArgumentsNumber Getter
byte OneSheeldClass::getArgumentNo()
{
  return argumentnumber;
} 
//ArgumentLength Getter
byte OneSheeldClass::getArgumentLength(byte x)
{
  return argumentL[x];
}
//Data Getter
byte * OneSheeldClass::getArgumentData(byte x)
{
  return arguments[x];
}

//Convert float to array of bytes
byte * OneSheeldClass::convertFloatToBytes(float data)
{
  convertFloatUnion.number = data;
  return convertFloatUnion.floatBytes;
} 

//Convert array of bytes to float
float OneSheeldClass::convertBytesToFloat(byte * data)
{
  convertFloatUnion.floatBytes[0] = data[0];
  convertFloatUnion.floatBytes[1] = data[1];
  convertFloatUnion.floatBytes[2] = data[2];
  convertFloatUnion.floatBytes[3] = data[3];
  return convertFloatUnion.number;
} 

//Incomming Frames processing 
void OneSheeldClass::processInput()
{
  while(OneSheeldSerial.available()){
    int data=OneSheeldSerial.read();
    if(data==-1)return;
     if(!framestart&&data==START_OF_FRAME)
          {
              freeMemoryAllocated();
              counter=0;
              framestart=true;
              arguments=0;
              argumentL=0;
              counter++;
              #ifdef DEBUG
              Serial.print("C1 ");
              #endif
          }
          else if(counter==4&&framestart)                      //data is the no of arguments
          {
              #ifdef DEBUG
              Serial.print("C4 ");
              #endif
              datalengthcounter=0;
              argumentcounter=0;
              argumentnumber=data;
              counter++;
          }
          else if(counter==5&&framestart)                      //data is the no of arguments
          {
              #ifdef DEBUG
              Serial.print("C5 ");
              #endif
              if((255-argumentnumber)==data&&argumentnumber==0){
                counter=9;
                continue;
              }
              else if((255-argumentnumber)==data){
              arguments=(byte**)malloc(sizeof(byte*)*argumentnumber);//new byte*[argumentnumber];          //assigning the first dimension of the pointer (allocating dynamically space for 2d array)
              #ifdef DEBUG
              Serial.print("M1 ");
              #endif
              isArgumentsNumberMalloced=true;
              argumentL=(byte*)malloc(sizeof(byte)*argumentnumber);//new byte [argumentnumber];
              #ifdef DEBUG
              Serial.print("M2 ");
              #endif
              isArgumentLengthMalloced=true;
              counter++;
              }
              else{
                framestart=false;
                continue;
              }


          }
          else if (counter==6&&framestart)                    // data is the first argument length
          {
              #ifdef DEBUG
              Serial.print("C6 ");
              #endif
              argumentL[argumentcounter]=data;
              counter++;
          }
          else if (counter==7&&framestart)                    // data is the first argument Data information
          {
            #ifdef DEBUG
            Serial.print("C7 ");
            #endif
            if((255-argumentL[argumentcounter])==data){
              arguments[argumentcounter]=(byte*)malloc(sizeof(byte)*argumentL[argumentcounter]); // assigning the second dimensional of the pointer
              #ifdef DEBUG
              Serial.print("M3 ");
              #endif
              numberOfDataMalloced++;
              counter++;
            }
            else{
                framestart=false;
                continue;
              }
          }
          else if (counter==8&&framestart)
          {
              #ifdef DEBUG
              Serial.print("C8 ");
              #endif
              arguments[argumentcounter][datalengthcounter++]=data;
              if (datalengthcounter==argumentL[argumentcounter])
              {
                  datalengthcounter=0;
                  argumentcounter++;
                  if(argumentcounter==argumentnumber)
                  {
                    counter++;                                    //increment the counter to take the last byte which is the end of the frame

                  }
                  else
                  {
                       counter=6;

                  }

              }

          }
          else if(counter==9&&framestart)
          {
              #ifdef DEBUG
              Serial.print("C9 ");
              #endif
            endFrame=data;
              if(endFrame==END_OF_FRAME)                                   //if the endframe is equal to zero send to shields and free memory
              {
                      sendToShields();
                      freeMemoryAllocated();
                      
              }
              else                                            //if endframe wasn't equal to zero make sure that the memory is free anyway
              {
                freeMemoryAllocated();
              }
          }
          else if(framestart){
                if(counter==1){
                  shield=data;
                  bool found = false;
                  for (int i=0;i<28;i++) {
                    if (shield == inputShieldsList[i]){
                      found = true;
                      
                    }
                  }
                  if (!found) {
                    framestart=false;
                    continue;
                  }
                }
                else if(counter==2){
                  instance=data;
                  #ifdef DEBUG
                  Serial.print("C2 ");
                  #endif
                }
                else if(counter==3){
                  functions=data;
                  #ifdef DEBUG
                  Serial.print("C3 ");
                  #endif
                }
            counter++;
          }
      }
    }

void OneSheeldClass::freeMemoryAllocated(){
  framestart=false;
  if(isArgumentsNumberMalloced){
          for(int i=0;i<numberOfDataMalloced;i++)
          {
            free(arguments[i]);
            #ifdef DEBUG
            Serial.print("F3 ");
            #endif
          }
          numberOfDataMalloced=0;
          free(arguments);
          #ifdef DEBUG
          Serial.print("F1 ");
          #endif
          isArgumentsNumberMalloced=false;
        }
        if(isArgumentLengthMalloced){
          free(argumentL);
          #ifdef DEBUG
          Serial.println("F2 ");
          #endif
          isArgumentLengthMalloced=false;
        }
}
void OneSheeldClass::listenToRemoteOneSheeld(RemoteOneSheeld * oneSheeld)
{
  if(remoteOneSheeldsCounter<MAX_REMOTE_CONNECTIONS)
  listOfRemoteOneSheelds[remoteOneSheeldsCounter++]=oneSheeld;
} 
//Data Sender to Input Shields
void OneSheeldClass::sendToShields()
{
  //Checking the Shield-ID    
  byte number_Of_Shield= OneSheeld.getShieldId();     
  switch (number_Of_Shield)
  {
    case ONESHEELD_ID            :processData();break;
    #ifdef KEYPAD_SHIELD
    case KEYPAD_SHIELD_ID        : Keypad.processData(); break ;
    #endif
    #ifdef GPS_SHIELD
    case GPS_ID                  : GPS.processData();break ;
    #endif
    #ifdef SLIDER_SHIELD
    case SLIDER_ID               : Slider.processData(); break;
    #endif
    #ifdef PUSH_BUTTON_SHIELD
    case PUSH_BUTTON_ID          : PushButton.processData();break;
    #endif
    #ifdef TOGGLE_BUTTON_SHIELD
    case TOGGLE_BUTTON_ID        : ToggleButton.processData();break;
    #endif
    #ifdef GAMEPAD_SHIELD
    case GAMEPAD_ID              : GamePad.processData();break;
    #endif
    #ifdef PROXIMITY_SHIELD
    case PROXIMITY_ID            : ProximitySensor.processData();break;
    #endif
    #ifdef MIC_SHIELD
    case MIC_ID                  : Mic.processData();break;
    #endif
    #ifdef TEMPERATURE_SHIELD
    case TEMPERATURE_ID          : TemperatureSensor.processData();break;
    #endif
    #ifdef LIGHT_SHIELD
    case LIGHT_ID                : LightSensor.processData();break;
    #endif
    #ifdef PRESSURE_SHIELD
    case PRESSURE_ID             : PressureSensor.processData();break;
    #endif
    #ifdef GRAVITY_SHIELD
    case GRAVITY_ID              : GravitySensor.processData();break;
    #endif
    #ifdef ACCELEROMETER_SHIELD
    case ACCELEROMETER_ID        : AccelerometerSensor.processData();break;
    #endif
    #ifdef GYROSCOPE_SHIELD
    case GYROSCOPE_ID            : GyroscopeSensor.processData();break;
    #endif
    #ifdef ORIENTATION_SHIELD
    case ORIENTATION_ID          : OrientationSensor.processData();break;
    #endif
    #ifdef MAGNETOMETER_SHIELD
    case MAGNETOMETER_ID         : MagnetometerSensor.processData();break;
    #endif
    #ifdef PHONE_SHIELD
    case PHONE_ID                : Phone.processData();break;
    #endif
    #ifdef SMS_SHIELD
    case SMS_ID                  : SMS.processData();break;
    #endif
    #ifdef CLOCK_SHIELD
    case CLOCK_ID                : Clock.processData();break;
    #endif
    #ifdef KEYBOARD_SHIELD
    case KEYBOARD_ID             : AsciiKeyboard.processData();break;
    #endif
    #ifdef TWITTER_SHIELD
    case TWITTER_ID              : Twitter.processData();break;
    #endif
    #ifdef VOICE_RECOGNITION_SHIELD
    case VOICE_RECOGNITION_ID    : VoiceRecognition.processData();break;
    #endif
    #ifdef TERMINAL_SHIELD
    case TERMINAL_ID             : Terminal.processData();break;
    #endif
    #ifdef REMOTE_SHIELD
    case REMOTE_SHEELD_ID        : for(int i=0;i<remoteOneSheeldsCounter;i++)
                                    listOfRemoteOneSheelds[i]->processData();
                                    if(isOneSheeldRemoteDataUsed)
                                    processRemoteData();
                                    break;
    #endif
  }
}
#ifdef REMOTE_SHIELD
void OneSheeldClass::setOnNewMessage(void (*userFunction)(char * address, char * key, float value))
{
  changeFloatCallBack = userFunction;
  isSetOnFloatMessageInvoked = true;
  isOneSheeldRemoteDataUsed=true;
}

void OneSheeldClass::setOnNewMessage(void (*userFunction)(String address, String key, float value))
{
  changeFloatCallBackWithString = userFunction;
  usedSetOnFloatWithString = true;
  isOneSheeldRemoteDataUsed=true;
}


void OneSheeldClass::setOnNewMessage(void (*userFunction)(char * address, char * key, char * value))
{
  changeStringCallBack = userFunction;
  isSetOnStringMessageInvoked = true;
  isOneSheeldRemoteDataUsed=true;
}

void OneSheeldClass::setOnNewMessage(void (*userFunction)(String address, String key, String value))
{
  changeStringCallBackWithString = userFunction;
  usedSetOnStringWithString = true;
  isOneSheeldRemoteDataUsed=true;
}

void OneSheeldClass::processRemoteData()
{
  byte functionId = getFunctionId();

  if(functionId == READ_MESSAGE_FLOAT)
  {
    char remoteAddress[37];
    memcpy(remoteAddress,getArgumentData(0),36);
    remoteAddress[36]='\0';  // processed the remote address 

    int keyLength = getArgumentLength(1);
    char key[keyLength+1];
    memcpy(key,getArgumentData(1),keyLength);
    key[keyLength]='\0';

    float incomingValue = convertBytesToFloat(getArgumentData(2));

    if(isSetOnFloatMessageInvoked)
    (*changeFloatCallBack)(remoteAddress,key,incomingValue);

    if(usedSetOnFloatWithString)
    {
      String remoteAddressInString(remoteAddress);
      String keyInString(key);
      (*changeFloatCallBackWithString)(remoteAddressInString,keyInString,incomingValue);
    }

  }
  else if(functionId == READ_MESSAGE_STRING)
  {
    char remoteAddress[37];
    memcpy(remoteAddress,getArgumentData(0),36);
    remoteAddress[36]='\0';  // processed the remote address 

    int keyLength = getArgumentLength(1);
    char key[keyLength+1];
    memcpy(key,getArgumentData(1),keyLength);
    key[keyLength]='\0';
    
    int stringDataLength = getArgumentLength(2);
    char stringData[stringDataLength+2];
    memcpy(stringData,getArgumentData(2),stringDataLength);
    stringData[stringDataLength]='\0';

    if(isSetOnStringMessageInvoked)
    (*changeStringCallBack)(remoteAddress,key,stringData);

    if(usedSetOnStringWithString)
    {
      String remoteAddressInString(remoteAddress);
      String keyInString(key);
      String stringDataInString(stringData);
      (*changeStringCallBackWithString)(remoteAddressInString,keyInString,stringDataInString);
    }

  }
}
#endif

void OneSheeldClass::processData(){
  byte functionId = getFunctionId();
  //Check  the function ID 
  if(functionId == DISCONNECTION_CHECK_FUNCTION)
  {
      isOneSheeldConnected=false;
  }
  else if(functionId == CONNECTION_CHECK_FUNCTION)
  {
      isOneSheeldConnected=true;
  }
  else if(functionId == LIBRARY_VERSION_REQUEST)
  {
    sendPacket(ONESHEELD_ID,0,SEND_LIBRARY_VERSION,0);
  }
}

static unsigned long analogReadtimeout = 1000000L;

//PulseWidthModulation Getter 
unsigned char OneSheeldClass::analogRead(int pin)
{
    double period=(double)pulseIn(pin,HIGH,analogReadtimeout)+(double)pulseIn(pin,LOW,analogReadtimeout);
    double duty=(double)pulseIn(pin,HIGH,analogReadtimeout);
    double fraction=duty/period;
    unsigned char pwm_out=(unsigned char)(ceil)(fraction*255);
    return pwm_out;
}

//Instantiating Object
#if defined(__AVR_ATmega32U4__) || (defined(ARDUINO_LINUX) && !defined(PCDUINO))
OneSheeldClass OneSheeld(Serial1);
void serialEvent1()
#else
OneSheeldClass OneSheeld(Serial);
void serialEvent()
#endif
{
#ifdef PCDUINO
  Serial.process_recv();
#endif
  OneSheeld.processInput();      
}
