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

void setup()
{
  //printer
  pinMode(7, OUTPUT); digitalWrite(7, LOW);
  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)
  printer.upsideDownOn();
  printer.setSize('L'); 
  //wire
  Wire.begin(1);
  Serial.begin(19200);
  Wire.onReceive(receiveEvent);
 
}

void loop()
{
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
  
  Serial.println(recevedMessage);         // print the integer
  splitString();
  
}

void printing(){
  printer.println("");
  printer.println(line4);
  printer.println(line3);
  printer.println(line2);
  printer.println(line1);
  printer.feed(2);
  printer.sleep();      // Tell printer to sleep
  delay(3000L);         // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
  //printer.setDefault(); // Restore printer to defaults
  somethingToPrint = false;
}

void splitString(){
	line1 = recevedMessage.substring(0,16);
	line2 = recevedMessage.substring(16,31);
	line3 = recevedMessage.substring(31,46);
	line4 = recevedMessage.substring(46,61);
	somethingToPrint = true;
}

void splitAndReturn(){
	recevedMessage
}