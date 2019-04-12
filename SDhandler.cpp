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

//Bør denne returnere en linje som string eller håndtere hele serialdumpingen?
void SDhandler::ReadFromCard(String fileName)
{
	if (SD.exists(fileName))
	{
		file = SD.open(fileName, FILE_READ);
		Serial.println("#READ#");
		while (file.available())
		{
			Serial.write(file.read());
		}
		file.close();
		Serial.println("#DONE#");
	}
}

void SDhandler::ChangeConfig(String config,String fileName) // s1000010000# , 10000 ms, 10000 ganger
{
	if (SD.exists(fileName)) 
		SD.remove(fileName);
	file = SD.open(fileName,FILE_WRITE);
	Serial.println(config.substring(1, 6));
	Serial.println(config.substring(6, 11));
	file.println(config.substring(1,6));
	file.println(config.substring(6, 11));
	file.close();
}

void SDhandler::Boot(unsigned int parameters[], int numberOfparameters,String fileName)
{
	parameters[0] = 60000;
	parameters[1] = 90;

	if (SD.exists(fileName)) 
	{
		String line="";
		char a;
		file = SD.open(fileName, FILE_READ);
		for (int i = 0; i < numberOfparameters; i++)
		{
			
			while (file.available())
			{
				a = file.read();
				
				if(a=='\n') break;
				else line += a;
			}
			parameters[i] = line.toInt();
			line = "";
		}
		file.close();
	}
	

}

void SDhandler::WriteToCard(String string, String fileName)
{	
	file = SD.open(fileName, FILE_WRITE);
	file.println(string);
	file.close();
}


void SDhandler::EraseFile(String fileName)
{
	if(SD.exists(fileName))
	{
		SD.remove(fileName);
	}
}
