#ifndef SDhandler_h
#define SDhandler_h

#include "Arduino.h"
#include <SPI.h>
#include <SD.h>

class SDhandler
{
	public:
		SDhandler();
		void Begin(int pin);
		void ReadFromCard(String fileName);
		
		void ChangeConfig(String config,String fileName);
		void Boot(unsigned int parameters[], int numberOfparameters,String filename);

		void WriteToCard(String string,String filename);
		void EraseFile(String fileName);
	private:
		File file;
};

#endif SDhandler_h