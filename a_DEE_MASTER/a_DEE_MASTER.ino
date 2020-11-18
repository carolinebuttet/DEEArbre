// All global variables and imports go here

#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>


// DEBUG MODE: 
// Change this to true if you want to debug 
// Always queries the same page (currPage)
// Does not save last query to SD card
// Always sends a message to slave number 1
bool DEBUG_ENABLED = false;
int POST_INTERVAL = 3;

// ETHERNET 
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // The mac address of the shield
IPAddress ip(192, 168, 0, 177); // The ip address of the shield
IPAddress myDns(192, 168, 0, 1);
EthernetClient client; 
char server[] = "www.vanderlanth.io"; 
String host = "Host: vanderlanth.io";
String path = "/sub/dee/fr/event.json/page:"; // url: https://vanderlanth.io/sub/dee/fr/event.json/page:17
unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
const unsigned long postingInterval = POST_INTERVAL*1000;  // delay between the page request, in milliseconds
bool isRequestSuccesful = true;


// SD CARD
int currId = -1 ;
int currPage = 1;
File myFile;
char buffer[6];
String currentFileName = "test.txt"; //the name of the text file that stores the last visited page
String backupFileName = "backup.txt"; //the name of the backup file that stores the last visited page


// I2C
int activePrinter = 1;
int printerQuantity = 7;
int bufferSize = 32;
byte x = 0;
