/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>

File myFile;

char buffer[6];
int  currPage;

int testValue = 1;

String currentFileName = "test.txt";
String backupFileName = "backup.txt";

void setup() {
  
  initSDCard();
  bool doesFileExist = openFile(currentFileName);
  if(!doesFileExist){
    Serial.println("file does not exist, look for a backup");
    bool doesBackupExist = openFile(backupFileName);
    if(doesBackupExist){
        Serial.println("backup found");
        myFile.close();
        SD.remove(backupFileName);
        saveNewValue(backupFileName, String(testValue));
        myFile.close();
        SD.remove(currentFileName);    
        saveNewValue(currentFileName , String(testValue));
        myFile.close();
     }else{
        Serial.println("no backup found");
        SD.remove(backupFileName);
        saveNewValue(backupFileName, String(testValue));
        myFile.close();
        SD.remove(currentFileName);  
        saveNewValue(currentFileName , String(testValue));
        myFile.close();
      }
   }
   else{
    Serial.println("file exists!");
     //remove the first file
    myFile.close();
    SD.remove(backupFileName);
    saveNewValue(backupFileName, String(testValue));
    myFile.close();
    SD.remove(currentFileName);    
    saveNewValue(currentFileName , String(testValue));
    myFile.close();
   }

   //check the backup file just to be sure
   bool test = openFile(backupFileName);
   myFile.close();
}

void loop() {
  // nothing happens after setup
}

void initSDCard(){
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    
    Serial.print("Initializing SD card...");
  
    if (!SD.begin(4)) {
      Serial.println("initialization failed!");
      while (1);
    }
  Serial.println("initialization done.");
 }

 bool openFile(String fileName){
  Serial.print("opening file ");
  Serial.println(fileName);
  // Open the file for reading:
  myFile = SD.open(fileName);
  if (myFile) {
    char character;
    int index = 0;
    while((character = myFile.read()) != -1){
      buffer[index] = character;
      index ++;
    }
    // close the file:
    myFile.close();
    currPage = atoi(buffer);
    Serial.println("currpage = ");
    Serial.println(currPage); 
    return true;   
  } else {
    Serial.print("error opening ");
    Serial.println(fileName);
    myFile.close();
    return false;
  }
 }

 void saveNewValue(String fileName, String value){
  Serial.print("saveNewValue ");
  Serial.print(value);
  Serial.print(" into ");
  Serial.println(fileName);
  myFile.close();
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(fileName, FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to ");
    Serial.println(fileName);
    myFile.println(value);
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.print("error opening ");
    Serial.println(fileName);
    myFile.close();
  }
 }
