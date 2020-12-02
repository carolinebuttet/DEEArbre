
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
      
   line[index] = c;         // we store all the received characters in a single array
   index++;                 // we increment the index
      
  }

  bool isMessageComplete = messageComplete(line);  // we check if the line we received is the -END- Message
  if(isMessageComplete) {                          // if the message is complete
    String message = receivedMessage[0];           // we get the message
    processMessageForPrint(message);               // and we process it for printing (word wrap), in e_DEE_StringSplit
    numLines = 0;     // we reset the numlines to 0
    for(int j = 0; j< 10; j++){
      for(int i = 0; i< 32; i++){
        receivedMessage[j][i]=0; 
      }
    }
  }
 
  else{                                            // if the message is not complete  
    for(int i = 0 ; i<numBytes; i++){              // Add the current line to the message array
      receivedMessage[numLines-1][i] = line[i];
    }
  }
}

bool messageComplete(char currentLine[32] ){       // This function returns ture if the message is complete.
  //Serial.println(currentLine);
  bool isMatch = true;
  for(int i =0; i< 5; i++){                        // We compare the characters of the current line to the end message
    char c = currentLine[i];                       // If thes match, this means that the message is complete
    char endMessageChar = endMessage[i];
    if(c == endMessageChar){
      isMatch = true;
    }
    else{
      isMatch = false;
      return isMatch;
      }
    }
  return isMatch;                                  // We return true or false
 }
