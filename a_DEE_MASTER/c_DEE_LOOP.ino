//THE LOOP FUNCTION

void loop() {

    // if 5 seconds have passed since your last connection,
    // then connect again and send data:
    if (millis() - lastConnectionTime > postingInterval) {
      Watchdog.reset();
      httpRequest(); //Request the data (in d_DEE_ETHERNET)

      //If the request is succesful
      if(isRequestSuccesful) { 
        parseData(); // Parse the data and send it over vis I2C (in d_DEE_ETHERNET)
        if(!DEBUG_ENABLED){ // if we are not in debug mode
          saveActivePageToSdCard(); // Save the last visited page to the SD card (in f_DEE_SD_CARD)
        }
      };      
    }
    
    
}
