// Printer stuff goes here!

void printMessage(String messageArray[], int numLinesForCurrentMessage ){
  //Le message a a forme suivante: 
  //In array d'une longueur égale à n (numLinesForCurrentMessage)
  
  //Il faut itérer dans chaque entrée de l'array pour trouver un String comme ici: 
  Serial.print("... Printing following message into ");
  Serial.print(numLinesForCurrentMessage);
  Serial.println(" lines ...");
  for(int j = 0; j< numLinesForCurrentMessage; j++){
    String line = messageArray[j];
     Serial.println(line);  
  }
}
