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

//B�r denne returnere en linje som string eller h�ndtere hele serialdumpingen?
void SDhandler::ReadFromCard(String fileName)
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
