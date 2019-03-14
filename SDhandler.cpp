#include "SDhandler.h"

SDhandler::SDhandler(int _pin)
{
	SD.begin(_pin);
}

void SDhandler::ReadFromCard()
{
}

void SDhandler::WriteToCard(String string, String filename)
{
	
	file = SD.open(fileName, FILE_WRITE);

	Serial.print(string);
	file.println(string);
	file.close();
}
