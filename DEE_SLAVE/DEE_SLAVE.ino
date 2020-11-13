#include <Wire.h>
//Set this to false to test the device with real conditions.
bool DEBUG_ENABLED = true;

char receivedMessage[10][32];
char endMessage[5] = "-END-";
int numLines = 0;
int maxCharsForPrinter = 15;
int numLinesForCurrentMessage=1;
