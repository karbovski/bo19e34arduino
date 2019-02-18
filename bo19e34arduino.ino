#include <Wire.h>
#include <RTClib.h>	
#include <SPI.h>
#include <SD.h>

#define fileName  "fil.txt"

RTC_DS1307 rtc;
File file;


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
	SD.begin(10);
	if (!rtc.begin())
		Serial.println("Could not find RTC");
	//rtc.adjust(DateTime(2019, 2, 8, 18, 30, 0));
}

void loop() {

	if (Serial.available())
	{
		String inputString = Serial.readStringUntil('#');

		char command = inputString.charAt(0);
		if (command == 'w') writeToCard();
		else if (command == 'r') readFromCard();
		else if (command == 'e') SD.remove(fileName);
		else if (command == 'c') adjustClock(inputString);
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

void writeToCard()
{
	Serial.print("Saving: ");
	file = SD.open(fileName, FILE_WRITE);

	Serial.println(getTheDate());
	file.println(getTheDate());
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
	String string = "";
	char buffer[2];
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