//i2c related code (Communication to the slaves)

//Initialze the I2C protocol
void initI2C(){
  Serial.println("initializing I2C...");
  Wire.begin(); // join i2c bus (address optional for master)
}

// This function increments the activeprinter value (the slave to which the info will be sent)
// and calls the sendMessage() function
void dispatch(const char* Message){
  const char* message = Message; 
  sendMessage(activePrinter, message);
  if(!DEBUG_ENABLED){
    activePrinter++; //passage à l'imprimante suivante au prochain message.
  }
  
  if(activePrinter > printerQuantity){ // si supérieur au nombre de printer retour au premier.
    activePrinter = 1;
  }
}

// This function sends the message to the slave via i2c
// It will break the message in chunks of 32 chars
// And send an end message at the end ( endMessage )

void sendMessage(int ActivePrinter, const char* Message){
  int activePrinter = ActivePrinter;
  const char* message = Message;
  if(DEBUG_ENABLED){ // if we are in debug mode, we send this message, that can be changed for testing.
    message = "Et voici l'alphabet, attention: ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //message = "Joyeux Noël à tout le monde les amis et une bien heureuse année à tous! Voici un message encore un peu plus long pour vous dire que je suis née le 14 novembre 1990 à 17:34. Ciao!";
  }
 
  const char* endMessage = "-END-";
  
  //Split the text in bits of 32 chars:
  Serial.println("sending the following:");
  Serial.println(message);
  Serial.print("to slave number ");
  Serial.println(activePrinter);
  int num_chunks = ceil(strlen(message)/32)+1; // Determine how many chunks we'll need to send this message
  for(int i = 0 ; i< num_chunks; i++){ //For each chunk, create an array of 32 chars and send them over via i2c
    char line[32];
    for(int j = 0; j<32; j++){
        line[j] =  message[j+i*32];       
     }
     Wire.beginTransmission(activePrinter); // transmit to device
     Wire.write(line);   // Send the line
     Wire.endTransmission();    // stop transmitting  
  }
  //Send an end message
  Wire.beginTransmission(activePrinter); // transmit to device
  Wire.write(endMessage);  
  Wire.endTransmission();    // stop transmitting  
}
