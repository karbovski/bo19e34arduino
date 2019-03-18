#pragma once
#ifndef RTChandler_h
#define RTChandler_h

#include "Arduino.h"
#include <RTClib.h>	

class RTChandler
{
	public:
		RTChandler();
		String GetTheDate();
		void AdjustClock(String inputString);

	private:
		RTC_DS1307 rtc;
		
};



#endif RTChandler_h
