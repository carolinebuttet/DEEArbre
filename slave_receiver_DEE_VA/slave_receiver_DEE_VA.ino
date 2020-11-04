#include <Wire.h>
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#define TX_PIN 4 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer
byte inByte;
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);
boolean somethingToPrint = false;
String recevedMessage = "Bonjour les copains je vais bien, et vous comment allez vous";

String line1 = "";
String line2 = "";
String line3 = "";
String line4 = "";

char lines [10] [15];
const int wantedLength = 15;
char str[] ="Hello World! Here is some text. I need them to split into multiple lines without breaking the words.";

void setup()
{
  //printer
  pinMode(7, OUTPUT); digitalWrite(7, LOW);
  mySerial.begin(19200);  // Initialize SoftwareSerial
  /*printer.begin();        // Init printer (same regardless of serial type)
  printer.upsideDownOn();
  printer.setSize('L'); 
  //wire
  Wire.begin(1);*/
  Serial.begin(115200);
  //Wire.onReceive(receiveEvent);
 
}

void loop()
{

	splitAndReturn();
	printLines();
	delay(1000);
  if(somethingToPrint){
    //printing();
  }
}

void receiveEvent()
{
  //recevedMessage="";
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    //recevedMessage += c;
  }
  
  //Serial.println(recevedMessage);         // print the integer
  //emptyLines();
  splitAndReturn();
  printLines();

  
}

void printing(){
	printer.println(""); //one empty line
	for (int i =  HowManyLines(); i >0; i--)
	{
		 printer.println(lines[i]); //print each line from array of String
		 Serial.println(lines[i]);
	}

	printer.feed(2);
	printer.sleep();      // Tell printer to sleep
	delay(3000L);         // Sleep for 3 seconds
	printer.wake();       // MUST wake() before printing again, even if reset
	//printer.setDefault(); // Restore printer to defaults
	somethingToPrint = false;
}
/*
void splitString(){
	line1 = recevedMessage.substring(0,16);
	line2 = recevedMessage.substring(16,31);
	line3 = recevedMessage.substring(31,46);
	line4 = recevedMessage.substring(46,61);
	somethingToPrint = true;
}
*/
void emptyLines(){
for (int i = 0; i < sizeof(lines); i++) //clean lines before filling them
  {
  	//lines[i]="";
  	//Serial.println("ok");
  }
}
void printLines(){
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			Serial.print(lines[i][j]);
			//lines[i][j]="";
		}
	 Serial.println();		
	}
}
void splitAndReturn(){
  int i = 0;
  int j = 0;
  /*for (int i = 0; i < sizeof(lines); i++) //clean lines before filling them
  {
  	lines[i] ="";
  	Serial.println(i);
  }*/
	const char * p = str;
	  // keep going until we run out of text
	while (*p)
	{   
	    // find the position of the space
	    const char * endOfLine = split (p, wantedLength); 
	    // display up to that
	    while (p != endOfLine)
	    {
	    	lines[i][j]=*p++;
	    	j++;
	    }
	  	  //Serial.print (*p++);
	    // finish that line
	    i++;
	    //Serial.println ();
	    // if we hit a space, move on past it
	    if (*p == ' ')
	      p++;
    }
    somethingToPrint = true;
}


const char * split (const char * s, const int length)
  {
  // if it will fit return whole thing
  if (strlen (s) <= length)
    return s + strlen (s);

  // searching backwards, find the last space
  for (const char * space = &s [length]; space != s; space--)
    if (*space == ' ')
      return space;
   
  // not found? return a whole line
  return &s [length];       
  } // end of split

const int HowManyLines(){
	int tempValue = 0;
	for (int i = 0; i < sizeof(lines); ++i)
	{
		if (lines[i] == "")
		{
			break;
		}
		tempValue ++;
	}
	Serial.print("tempValue : ");
	Serial.println(tempValue);
	return tempValue;
}