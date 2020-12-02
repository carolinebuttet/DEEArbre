//Everything that is Ethernet related goes here

//This function setsup the ethernet shield
void setupEthernet(){  
  while (!Serial) continue;

  // start the Ethernet connection:
  
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
  } else {
    Serial.print("DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
}


// This function requests the online webpage 
// and sets the isRequestSuccesful value to true or false
void httpRequest(){
   Serial.print("requesting page number ");
   Serial.println(currPage);
   // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    String pageUrl = "GET "+path+String(currPage)+" HTTP/1.0";
    
    //getting the current URL
    client.println(pageUrl);
    //client.println(F("GET /sub/dee/fr/event.json/page:1"));
    
    client.println(host);
    client.println(F("Connection: close"));
    if (client.println() == 0) {
      Serial.println(F("Failed to send request"));
      isRequestSuccesful = false;
      client.stop();
      Watchdog.reset();
      return;
    }
    
    // Check HTTP status
    char status[32] = {0};
    client.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
      Serial.print(F("Unexpected response: "));
      Serial.println(status);
      isRequestSuccesful = false;
      lastConnectionTime = millis();
      client.stop();
      Watchdog.reset();
      return;
    }
    else{
      
      isRequestSuccesful = true;
      //increment the page to check
      if(!DEBUG_ENABLED){
        Serial.println("connection succesful, incrementing page to request.");
        currPage++;
        }else{
          
        Serial.println("connection succesful, not incrementing because DEBUG_ENABLED is true");
        }
        Watchdog.reset();
     }
  
    // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {
      Serial.println(F("Invalid response"));
      Watchdog.reset();
      client.stop();
      return;
    }
 
    
    // note the time that the connection was made:
    Watchdog.reset();
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    isRequestSuccesful = false;
    lastConnectionTime = millis();
    client.stop();
    Watchdog.reset();
    httpRequest();
    return;
  }
  
}


//This function parses the JSON
//And calls the dispatch function (in e_DEE_I2C)
//To send the message to the salves
void parseData(){
    const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(0) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 450;
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, client);
    //Change the structure here if the JSON's structure changes:
    const char* text = doc["data"][0]["text"]; 
    dispatch(text);    
}
