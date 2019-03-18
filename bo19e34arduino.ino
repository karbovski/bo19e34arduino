#include <RTClib.h>	
#include <SPI.h>
#include <SD.h>
#include "SDhandler.h"
#include "RTChandler.h"

#define FileName  "fil.txt"

const int PULSE_PIN = 4;
const int SD_PIN = 10;
const int BUTTON_PIN = 2;

RTChandler rtchandler;
SDhandler sdhandler(SD_PIN);

/*
	SD
		Clk	->	pin 13
		DO ->	pin 12
		DI ->	pin 11
		CS ->	pin 10
					
	RTC				
		SCL ->	A5	
		SDA ->	A4	

*/

void setup() {

	Serial.begin(9600);
	Serial.println("Connected");
	pinMode(PULSE_PIN, INPUT);
	pinMode(SD_PIN, OUTPUT);
	pinMode(BUTTON_PIN, INPUT);
}

void loop() {
	
	if (Serial.available() > 0)
	{
		String inputString = Serial.readStringUntil('#');
		Serial.println(inputString);
		char command = inputString.charAt(0);
		if (command == 'r') sdhandler.ReadFromCard(FileName);
		else if (command == 'e') SD.remove(FileName); // e# sletter SD kort filen
		else if (command == 'c') rtchandler.AdjustClock(inputString); // c20190219120800# gir 19.02.1997 12:09:00
	}

	if (digitalRead(BUTTON_PIN) == HIGH)
	{
		Serial.println("ButtonClicked");
		sdhandler.WriteToCard( measure(600000), FileName);
	}
	
}

String measure(unsigned int time)
{
	int startTime = millis();
	int count = 0;
	unsigned long duration;
	String ret = rtchandler.GetTheDate();

	while ((unsigned long)(millis() - millis()) <= time)
	{
		duration = pulseIn(PULSE_PIN, HIGH);
		if (duration != 0)
		{
			count++;
		}
	}

	return ret + ": " + count;
}








