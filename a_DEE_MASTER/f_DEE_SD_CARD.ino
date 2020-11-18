//SD card code

//This function initializes the SD card
void initSDCard(){
  Serial.print("Initializing SD card...");
    if (!SD.begin(4)) {
      Serial.println("initialization failed!");
      while (1);
    }
  Serial.println("initialization done.");
 }

 // this function gets the SD card info
 // so that we know if the device has already visited pages
void getSDCardInfo(){
  if(DEBUG_ENABLED){
    Serial.println("Debug mode is enabled, bypassing SD card info...");
    return;
  }
  Serial.println("get SD card info!");
  bool doesFileExist = openFile(currentFileName);
  if(!doesFileExist){
    bool doesBackupExist = openFile(backupFileName);
    if(doesBackupExist){
        myFile.close();
        SD.remove(backupFileName);
        saveNewValue(backupFileName, String(currPage));
        myFile.close();
        SD.remove(currentFileName);    
        saveNewValue(currentFileName , String(currPage));
        myFile.close();
     }else{
        SD.remove(backupFileName);
        saveNewValue(backupFileName, String(currPage));
        myFile.close();
        SD.remove(currentFileName);  
        saveNewValue(currentFileName , String(currPage));
        myFile.close();
      }
   }
   else{
    myFile.close();
    SD.remove(backupFileName);
    saveNewValue(backupFileName, String(currPage));
    myFile.close();
    SD.remove(currentFileName);    
    saveNewValue(currentFileName , String(currPage));
    myFile.close();
   }

   //check the backup file just to be sure
   bool test = openFile(backupFileName);
   myFile.close();
}


// Open a file and get the value that's inside it.
 bool openFile(String fileName){
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
    currPage = atoi(buffer); // Set currPage to the value that is inside the txt file
    
    return true;   
  } else {
    Serial.print("error opening ");
    Serial.println(fileName);
    myFile.close();
    return false;
  }
 }


//Save the new value to the SD card
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
    myFile.println(value);
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.print("error opening ");
    Serial.println(fileName);
    myFile.close();
  }
 }

//We save the active page to the SD card (currPage)
void saveActivePageToSdCard(){
  Serial.print("saving page ");
  Serial.print(currPage);
  Serial.println("to SD card");
  SD.remove(backupFileName);
  saveNewValue(backupFileName, String(currPage));
  myFile.close();
  SD.remove(currentFileName);    
  saveNewValue(currentFileName , String(currPage));
  myFile.close();
  }
 
