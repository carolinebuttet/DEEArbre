// Printer stuff goes here!

void printMessage(String messageArray[], int numLinesForCurrentMessage ){
  //Le message a a forme suivante: 
  //In array d'une longueur égale à n (numLinesForCurrentMessage)
  
  //Il faut itérer dans chaque entrée de l'array pour trouver un String comme ici: 
  Serial.print("... Printing following message into ");
  Serial.print(numLinesForCurrentMessage);
  Serial.println(" lines ...");


  //Iterate throught the arrays of Strings to print the line
  /*
  for(int j = 0; j< numLinesForCurrentMessage; j++){
    String line = messageArray[j];
    printLine(line);
  }*/
  
  //Or do it backwards:
  
  for(int j = numLinesForCurrentMessage-1; j>= 0; j--){
    String line = messageArray[j];
    printLine(line);
  }
  
  
}

void printLine(String line){
    Serial.print("Printing line: ");
    Serial.println(line);
  }
