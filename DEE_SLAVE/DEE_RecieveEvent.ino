
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent() {
  int index = 0;
  int numBytes = Wire.available();
  char line[numBytes];
  numLines++;

  while(Wire.available())
  {
    char c = Wire.read();    // receive a byte as character
    line[index] = c;
    index++;
  }
  //Serial.println("");
  bool isMessageComplete = messageComplete(line);
  if(isMessageComplete) {
    String message = receivedMessage[0];
    processMessageForPrint(message);
    numLines = 0;   
  }
 
  else{
    //Add the current line to the message array
    for(int i = 0 ; i<numBytes; i++){
      receivedMessage[numLines-1][i] = line[i];
    }
    
  }

}

bool messageComplete(char currentLine[32] ){
  //Serial.println(currentLine);
  bool isMatch = true;
  for(int i =0; i< 5; i++){
    char c = currentLine[i];
    char endMessageChar = endMessage[i];
    if(c == endMessageChar){
      isMatch = true;
    }
    else{
      isMatch = false;
      return isMatch;
      }
    }
  return isMatch;
 }
