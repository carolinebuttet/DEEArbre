#include <Wire.h>
#include "Adafruit_Thermal.h"


#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

String data = "";
String currentLine = "";
bool hasPrinted = false;
bool isPrintNeeded = false;
bool isFinalMessage = false;
String pendingData = "";
int index = 0;

void setup()
{
  Wire.begin(2);
  Serial.begin(9600);
  Serial.println("SETUP");
  Wire.onReceive(receiveEvent);

  //Printer setup
  pinMode(7, OUTPUT); digitalWrite(7, LOW);
  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();   
  printer.upsideDownOn();
}

void printMessage(){
  Serial.println("PRINT !!!!");
  Serial.println(pendingData);
  printer.wake();
  printer.feed(2);
  printer.sleep();
  hasPrinted = true;
  pendingData = "";
}

void checkIfPrintIsNeeded(){
  if(isPrintNeeded && !hasPrinted){
      Serial.println("Printing Message");
      printMessage();
  }
}

void loop()
{
  checkIfPrintIsNeeded();
  delay(1000);
}

void receiveEvent()
{
  data = "";
  while( Wire.available()){
    data += (char)Wire.read(); 
    //Serial.println("char is");
    Serial.println((char)Wire.read());

  }
  Serial.println(data);
  if(isPrintNeeded == false){
    pendingData = data;
    
    isPrintNeeded = true;
    hasPrinted = false;
   }
}
