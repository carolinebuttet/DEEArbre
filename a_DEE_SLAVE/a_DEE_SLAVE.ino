#include <Wire.h>
// INCLUDE THERMAL PRINTER LIBRARY HERE!

//Debug mode will print a local message instead of the message received over I2C
bool DEBUG_ENABLED = false;
int SLAVE_ID = 1;

char receivedMessage[10][32];
char endMessage[5] = "-END-"; //Attention: This has to match the end message on the master script.
int numLines = 0;
int maxCharsForPrinter = 15; // The line length for the printer
int numLinesForCurrentMessage=1;
