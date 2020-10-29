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

char server[] = "www.carolinebuttet.ch";  // also change the Host line in httpRequest()

unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10*1000;  // delay between updates, in milliseconds

int numPrinters = 7;
String messages [] = {"","","","","","",""};
int currId = -1 ;
  
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
  while (!Serial) continue;

  // start the Ethernet connection:
  /*
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
  */
  parseData();
}

void loop() {
    // if there's incoming data from the net connection.
    // send it out the serial port.  This is for debugging
    // purposes only:
    /*
    if (client.available()) {
      char c = client.read();
      Serial.write(c);
    }
  */
    // if 5 seconds have passed since your last connection,
    // then connect again and send data:
    if (millis() - lastConnectionTime > postingInterval) {
      //httpRequest();
      parseData();
     
    }
}


// Getting the info...
void httpRequest(){

   // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.println(F("GET /test_2.json HTTP/1.0"));
    client.println(F("Host: carolinebuttet.ch"));
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
  
    // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {
      Serial.println(F("Invalid response"));
      return;
    }
 
    
    // note the time that the connection was made:
    //lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
  
  
}

void parseData(){
    const size_t capacity = JSON_ARRAY_SIZE(7) + 8*JSON_OBJECT_SIZE(7) + 1880;
    DynamicJsonDocument doc(capacity);
    
    const char* json = "{\"caroline\":\"still the best!\",\"version\":\"https://jsonfeed.org/version/1\",\"title\":\"Feed\",\"description\":\"Hello, bonne année et joyeuse Pâques \n John Doe\",\"home_page_url\":\"http://localhost/base-kirby\",\"feed_url\":\"http://localhost/base-kirby/feed/\",\"items\":[{\"id\":\"http://localhost/base-kirby/home/article-1\",\"url\":\"http://localhost/base-kirby/home/article-1\",\"id_print\":\"0\",\"title\":\"article-1\",\"content_html\":\"Le message numero un\",\"date_published\":\"1970-01-01T00:00:00+00:00\",\"date_modified\":\"2020-10-07T14:26:18+00:00\"},{\"id\":\"http://localhost/base-kirby/home/article-2\",\"url\":\"http://localhost/base-kirby/home/article-2\",\"id_print\":\"1\",\"title\":\"article-2\",\"content_html\":\"Le message numero deux\",\"date_published\":\"1970-01-01T00:00:00+00:00\",\"date_modified\":\"2020-10-07T14:26:29+00:00\"},{\"id\":\"http://localhost/base-kirby/home/article-3\",\"url\":\"http://localhost/base-kirby/home/article-3\",\"id_print\":\"2\",\"title\":\"article-3\",\"content_html\":\"Le message numero trois\",\"date_published\":\"1970-01-01T00:00:00+00:00\",\"date_modified\":\"2020-10-07T14:26:54+00:00\"},{\"id\":\"http://localhost/base-kirby/home/article-4\",\"url\":\"http://localhost/base-kirby/home/article-4\",\"id_print\":\"3\",\"title\":\"article-4\",\"content_html\":\"Le message numero quatre\",\"date_published\":\"1970-01-01T00:00:00+00:00\",\"date_modified\":\"2020-10-07T14:27:16+00:00\"},{\"id\":\"http://localhost/base-kirby/home/article-5\",\"url\":\"http://localhost/base-kirby/home/article-5\",\"id_print\":\"4\",\"title\":\"article-5\",\"content_html\":\"Le message numero cinq\",\"date_published\":\"1970-01-01T00:00:00+00:00\",\"date_modified\":\"2020-10-07T14:27:31+00:00\"},{\"id\":\"http://localhost/base-kirby/home/artthfgklbf\",\"url\":\"http://localhost/base-kirby/home/artthfgklbf\",\"id_print\":\"5\",\"title\":\"artthfgklbf\",\"content_html\":\"Le message numero six\",\"date_published\":\"1970-01-01T00:00:00+00:00\",\"date_modified\":\"2020-10-08T11:55:35+00:00\"},{\"id\":\"http://localhost/base-kirby/home/oasdvhjkfbhjk\",\"url\":\"http://localhost/base-kirby/home/oasdvhjkfbhjk\",\"id_print\":\"6\",\"title\":\"oasdvhjkfbhjk\",\"content_html\":\"Le message numero sept\",\"date_published\":\"1970-01-01T00:00:00+00:00\",\"date_modified\":\"2020-10-07T14:28:08+00:00\"}]}";
    
    deserializeJson(doc, json);
    //deserializeJson(doc, json);
    //deserializeJson(doc, client);
    Serial.println("deserialization done");
    
    JsonArray items = doc["items"];
    for(int i = 0; i<= 6; i++){
      JsonObject item = items[i];
      const char* id = item["id_print"]; 
      const char* text = item["content_html"]; 
      int intId = atoi( id );
      //Serial.println(intId);
      //Serial.println(text);
      
      if(intId > currId){
        dispatch(text);
        currId++;
       }
       else{
         Serial.println("already sent");
         dispatch(text);
       }
    }
    
    Serial.println("end of parseData");
    //to delete when making internet request...
    lastConnectionTime = millis();
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
