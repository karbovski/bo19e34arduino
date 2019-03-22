#include "Arduino.h"
#include <RTClib.h>	
#include "RTChandler.h"

RTChandler::RTChandler()
{
	rtc.begin();
}

String RTChandler::GetTheDate()
{
	String string("");
	DateTime now = rtc.now();
	string += now.day;
	string += '/';
	string += now.month();
	string += '/';
	string += now.year();
	string += '/';
	string += now.hour();
	string += '/';
	string += now.minute();
	string += '/';
	string += now.second();
	return string;
}

// c20190219120800# gir 19.02.1997 12:09:00
void RTChandler::AdjustClock(String inputString)
{	
	int year = inputString.substring(1, 5).toInt();
	int month = inputString.substring(5, 7).toInt();
	int date = inputString.substring(7, 9).toInt();
	int hour = inputString.substring(9, 11).toInt();
	int minute = inputString.substring(11, 13).toInt();
	int second = inputString.substring(13, 15).toInt();
	rtc.adjust(DateTime(year, month, date, hour, minute, second));
}