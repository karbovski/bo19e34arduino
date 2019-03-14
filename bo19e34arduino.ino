//#include <Wire.h>
#include <RTClib.h>	
#include <SPI.h>
#include <SD.h>
#include <SDhandler.h>
#include <RTChandler.h>

#define fileName  "fil.txt"

const int pin = 7;
int SDpin = 10;
RTChandler rtchandler;
SDhandler sdhandler;


String measure(String inputString)
{
	unsigned int time = inputString.substring(1, inputString.length - 1).toInt();
	Serial.println(time);
	int startTime = millis();
	int count = 0;
	unsigned long duration;
	unsigned long avgLenght = 0;
	String ret = getTheDate();

	while ((unsigned long)(millis() - millis()) <= time)
	{
		duration = pulseIn(pin,HIGH);
		Serial.println(count);
	}

	return ret + ": " + count;
}


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
	
	
}

void loop() {

	if (Serial.available())
	{
		String inputString = Serial.readStringUntil('#');
		Serial.println(inputString);
		char command = inputString.charAt(0);
		if (command == 'w') writeToCard(getTheDate()); // w# skriver tidspunktet nå til SD
		else if (command == 'r') readFromCard(); // r# sender all data på SD over seriell
		else if (command == 'e') SD.remove(fileName); // e# sletter SD kort filen
		else if (command == 'c') adjustClock(inputString); // c20190219120800# gir 19.02.1997 12:09:00
		else if (command == 'm') measure(inputString); //m60000# måler i 60 sekunder
	}
	
}

void readFromCard()
{
	file = SD.open(fileName);
	while (file.available())
	{
		Serial.write(file.read());
	}
	file.close();
}

void writeToCard(String message)
{
	Serial.print("Saving: ");
	file = SD.open(fileName, FILE_WRITE);

	Serial.println(message);
	file.println(message);
	file.close();
}

void adjustClock(String inputString)
{
	//unsigned long inputString.substring(1,)
	int year = inputString.substring(1, 5).toInt();
	int month = inputString.substring(5, 7).toInt();
	int date = inputString.substring(7, 9).toInt();
	int hour = inputString.substring(9, 11).toInt();
	int minute = inputString.substring(11, 13).toInt();
	int second = inputString.substring(13, 15).toInt();
	rtc.adjust(DateTime(year, month, date, hour, minute, second));
}

String getTheDate()
{
	String string("");
	DateTime now = rtc.now();
	string += now.day();
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

