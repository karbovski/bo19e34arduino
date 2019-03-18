#include "Arduino.h"
#include <SD.h>
#include <SPI.h>
#include "SDhandler.h"

SDhandler::SDhandler()
{
}

void SDhandler::Begin(int pin)
{
	SD.begin(pin);
}



void SDhandler::ReadFromCard(String fileName)//Bør denne returnere en linje som string eller håndtere hele serialdumpingen?
{
	file = SD.open(fileName, FILE_READ);
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
