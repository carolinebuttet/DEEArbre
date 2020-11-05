#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>


// Initialize Ethernet library
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);

// initialize the library instance:
EthernetClient client;


//url: https://vanderlanth.io/sub/dee/fr/event.json/page:17
char server[] = "www.vanderlanth.io";  // also change the Host line in httpRequest()

unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 3*1000;  // delay between updates, in milliseconds

int currId = -1 ;
int currPage = 1;

//Printer stuff
int activePrinter = 1;
int printerQuantity = 7;
int bufferSize = 32;

byte x = 0;

void setup() {
  
  //i2c protocol
  Wire.begin(); // join i2c bus (address optional for master)
  
  // Initialize Serial port
  Serial.begin(9600);
  Serial.println("printing url");
  
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
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }

  delay(1000);
  
  //parseData();
 
}

void loop() {

  
    // if there's incoming data from the net connection.
    // send it out the serial port.  This is for debugging
    // purposes only:
    
    if (client.available()) {
      char c = client.read();
      Serial.write(c);
    }
  
    // if 5 seconds have passed since your last connection,
    // then connect again and send data:
    if (millis() - lastConnectionTime > postingInterval) {
      httpRequest();
      parseData();
     
    }
    
}


// Getting the info...
void httpRequest(){
   Serial.println("requesting page number");
   Serial.println(currPage);
   // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    String pageUrl = "GET /sub/dee/fr/event.json/page:"+String(currPage);
    
    //getting the current URL
    client.println(pageUrl);
    //client.println(F("GET /sub/dee/fr/event.json/page:1"));
    
    client.println(F("Host: vanderlanth.io"));
    client.println(F("Connection: close"));
    if (client.println() == 0) {
      Serial.println(F("Failed to send request"));
      return;
    }
    
    // Check HTTP status
    char status[32] = {0};
    client.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
      Serial.print(F("Unexpected response: "));
      Serial.println(status);
      return;
    }
    else{
      Serial.println("connection succesful, incrementing page to request.");
      //increment the page to check
      currPage++;
     }
  
    // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {
      Serial.println(F("Invalid response"));
      return;
    }
 
    
    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

void parseData(){
    const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(0) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 450;
    DynamicJsonDocument doc(capacity);
    const char* json = "{\"data\":[{\"id\":\"16\",\"text\":\"A long message with over 140 characters, this might be long and maybe event longer than this. A long message with over 140 characters, this might be long and maybe event longer than this. A long message with over 140 characters, this might be long and maybe event longer than this. A long message with over 140 characters, this might be long and maybe event longer than this.\"}],\"pages\":{},\"page\":17}";

    //deserializeJson(doc, json);
    deserializeJson(doc, client);

    const char* text = doc["data"][0]["text"]; 
    Serial.println("deserialization done");
    dispatch(text);
    
    Serial.println("end of parseData");
}



void dispatch(const char* Message){
  Serial.println("Dispatch!");
  const char* message = Message; 
  Serial.print("dispatching :");
  Serial.println(message);
  sendMessage(activePrinter, message);
  activePrinter++; //passage à l'imprimante suivante au prochain message.
  if(activePrinter > printerQuantity){ // si supérieur au nombre de printer retour au premier.
    activePrinter = 1;
  }
}

void sendMessage(int ActivePrinter, const char* Message){
  int activePrinter = ActivePrinter;
  const char* message = Message;
  Serial.print("sendMessage, beginTransmission to printer ");
  Serial.println(activePrinter);
  Wire.beginTransmission(activePrinter); // transmit to device #1
  Wire.write(message);  
  Wire.endTransmission();    // stop transmitting  
}
