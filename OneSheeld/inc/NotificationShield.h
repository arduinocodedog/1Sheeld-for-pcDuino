/*

  Project:       1Sheeld Library 
  File:          NotificationShield.h
                 
  Version:       1.0

  Compiler:      Arduino avr-gcc 4.3.2

  Author:        Integreight
                 
  Date:          2014.5

*/

#ifndef NotificationShield_h
#define NotificationShield_h

//Output Function ID
#define NOTIFICATION_NOTIFY_PHONE 0x01

class NotificationShieldClass 
{
public:
	//Sender 
	void notifyPhone(const char* );
	void notifyPhone(String );

private:

};

//Extern Object
extern NotificationShieldClass Notification;
#endif