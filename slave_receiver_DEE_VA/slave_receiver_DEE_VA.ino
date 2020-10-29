#include <Wire.h>
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#define TX_PIN 4 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer
byte inByte;
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);
boolean somethingToPrint = false;

void setup()
{
  //printer
  pinMode(7, OUTPUT); digitalWrite(7, LOW);
  mySerial.begin(19200);  // Initialize SoftwareSerial
  
  
  //wire
  Wire.begin(1);
  Serial.begin(19200);
  Wire.onReceive(receiveEvent);
  //printing();
}

void loop()
{
  delay(100);
  if(somethingToPrint){
    printing();
  }
}

void receiveEvent()
{
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
  somethingToPrint = true;
}

void printing(){
  printer.begin();        // Init printer (same regardless of serial type)
  printer.upsideDownOn();
  printer.setSize('L'); 
  printer.println(F("got something"));
  printer.feed(2);
  printer.sleep();      // Tell printer to sleep
  delay(200L);         // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault(); // Restore printer to defaults
  somethingToPrint = false;
}
