#include <Wire.h>
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#define TX_PIN 4 // Arduino transmit labeled RX on printer
#define RX_PIN 5 // Arduino receive  labeled TX on printer


const int id = 1; //id of the printer for I2C communication


byte inByte;
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);
const int numOfLine = 1;
const int numOfCharByLine = 15;
boolean messageNeedTobePrinted = false;
char lines [numOfLine] [numOfCharByLine];
String linesConverted [10];
String testString = "";
char linesTest[10][15] = {
{'H','e','l','l','o',' ','W','o','r','l','d',' ',' ',' ',' '},
{'B','o','n','n','e',' ','a','n','n',0x82,'e',' ','e','t',' '},
{'B','o','n','n','e',' ','s','a','n','t',0x82,' ','a',' ',' '},
{'t','o','u','s','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{'N','i','c','o','l','a','s',' ','N',' ',' ',' ',' ',' ',' '},
{},
{},
{},
{},
{}
};

void setup() {
  //printer
  pinMode(7, OUTPUT); digitalWrite(7, LOW);
  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)
  printer.setDefault(); // Restore printer to defaults
  printer.upsideDownOn();
  printer.setSize('L'); 
  //wire
  Wire.begin(id); 
  Wire.onReceive(receiveEvent);
  //serial for debuging
  Serial.begin(9600);
  
  //fillString();
  //printMessage();
  //endOfPrinting();
}

void loop() {
	if(messageNeedTobePrinted){
		//specialChar();
		//printMessage();
		Serial.println("ok");
	}
	delay(2000);
}

void receiveEvent()
{ 
  int i = 0;
  int j = 0;
  while (Wire.available()) { 
    byte c = Wire.read();
    if (c == 0x82)
    {
    	break;
    }
    lines[i][j]=c;
    j++;
    if (j>numOfCharByLine) i++;
  }
  messageNeedTobePrinted = true; 
}

void fillString(){
	for (int i = 0; i < numOfLine; ++i)
	{
		for (int j = 0; j < numOfCharByLine; ++j)
		{
			linesConverted[i]+= linesTest[i][j];
		}
		Serial.println(linesConverted[i]);
	}
}
void printMessage(){
	messageNeedTobePrinted = false;
	printer.feed(1);
	/*
	for (int i = 0; i < numOfLine; i++)
	{
		for (int j = 0; j < numOfCharByLine; ++j)
		{
			printer.write(lines[i][j]);
		}
		printer.println();
	}*/
	printer.write(0x82);
	printer.feed(2);
	
	
}

void endOfPrinting(){
	printer.sleep();      // Tell printer to sleep
  	delay(1000L);         // Sleep for 3 seconds
  	printer.wake();       // MUST wake() before printing again, even if reset
}

void specialChar(){
	for (int i = 0; i < numOfLine; ++i)
	{
		for (int j = 0; j < numOfCharByLine; ++j)
		{
			
		}
	}
}

