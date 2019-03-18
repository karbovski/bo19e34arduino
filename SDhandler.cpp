#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include "SDhandler.h"

SDhandler::SDhandler(int pin)
{
	//SD.begin(pin);
}

void SDhandler::ReadFromCard(String fileName)//Bør denne returnere en linje som string eller håndtere hele serialdumpingen?
{
	file = SD.open(fileName, FILE_WRITE);
	while (file.available())
	{
		Serial.write(file.read());
	}
	file.close();
}

void SDhandler::WriteToCard(String string, String fileName)
{
	
	file = SD.open(fileName, FILE_WRITE);
	file.println(string);
	file.close();
}
