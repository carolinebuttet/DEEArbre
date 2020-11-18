#include <Wire.h>

#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#define TX_PIN 4 // Arduino transmit labeled RX on printer
#define RX_PIN 5 // Arduino receive  labeled TX on printer
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);

//Debug mode will print a local message instead of the message received over I2C
bool DEBUG_ENABLED = false;
bool MSG_NEED_TO_BE_P = false;
int SLAVE_ID = 5;
String lines[10]; // An arrayy of String to store our final message
int numLinesS = 0;  

char receivedMessage[10][32];
char endMessage[5] = "-END-"; //Attention: This has to match the end message on the master script.
int numLines = 0;
int maxCharsForPrinter = 15; // The line length for the printer
int numLinesForCurrentMessage=1;
