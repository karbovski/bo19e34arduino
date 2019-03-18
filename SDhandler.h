//pragma once
#ifndef SDhandler_h
#define SDhandler_h

#include "Arduino.h"
#include <SPI.h>
#include <SD.h>

class SDhandler
{
	public:
		SDhandler(int pin);
		void ReadFromCard(String fileName);
		void WriteToCard(String string,String filename);
	private:
		File file;

};

#endif SDhandler_h