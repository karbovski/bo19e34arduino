#include <U8x8lib.h>
#include <U8g2lib.h>
#include <RTClib.h>	
#include <SPI.h>
#include <SD.h>
#include "SDhandler.h"
#include "RTChandler.h"

#define FileName  "fil.txt"
#define ConfigFile "config.txt"

const int PULSE_PIN = 4;		
const int SD_PIN = 10;
const int BUTTON_PIN = 2;

//Variabler som brukes i måling
unsigned int measureTime;

RTChandler rtchandler;
SDhandler sdhandler;

/*
	SD
		Clk	->	pin 13
		DO ->	pin 12
		DI ->	pin 11
		CS ->	pin 10
	RTC				
		SCL ->	A5	
		SDA ->	A4	

	LCD

#define CLOCK 13
#define DATA 12
#define CS 11
#define DC 10
#define RESET 9
*/

void setup() {
	Serial.begin(9600);
	sdhandler.Begin(SD_PIN);
	measureTime = 10000;
	pinMode(PULSE_PIN, INPUT);
	pinMode(SD_PIN, OUTPUT);
	pinMode(BUTTON_PIN, INPUT);
}

void loop() {
	
	if (Serial.available() > 0)
	{
		String inputString = Serial.readStringUntil('#');
		//Serial.println(inputString);
		char command = inputString.charAt(0);
		if (command == 'r')
		{
			Serial.println("Reading SD");
			sdhandler.ReadFromCard(FileName);
			Serial.println("Done");
		}
		else if (command == 'e')
		{
			Serial.println("Erasing file");
			sdhandler.EraseFile(FileName);
			Serial.println("Done");
		}
		else if (command == 'c') rtchandler.AdjustClock(inputString); // c20190219120800# gir 19.02.1997 12:09:00
	}

	if (digitalRead(BUTTON_PIN) == HIGH)
	{
		Serial.println("Measuring: ");
		String result = measure(measureTime);
		Serial.println(result);
		sdhandler.WriteToCard(result, FileName);
	}
}

// måler i 'time' antall sekunder og returnerer
String measure(unsigned int time)
{
	unsigned long startTime = millis();
	unsigned long currentTime = startTime;
	unsigned long count = 0;
	unsigned long duration;
	String ret = rtchandler.GetTheDate();
	
	do
	{
		duration = pulseIn(PULSE_PIN, HIGH);
		if (duration != 0)
		{
			count++;
		}
		currentTime = millis();
	} while ((unsigned long)(currentTime-startTime) <= time);

	return ret + ": " + count + ": " + (currentTime - startTime);
}



