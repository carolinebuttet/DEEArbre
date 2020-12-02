//THE SETUP FUNCTION

void setup() {
  
  //printer
  pinMode(7, OUTPUT); digitalWrite(7, LOW);
  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)
  printer.setDefault(); // Restore printer to defaults
  printer.upsideDownOn();
  printer.setSize('L'); 

  //Wire
  Wire.begin(SLAVE_ID);                       // join i2c bus with address
  Wire.onReceive(receiveEvent);               // register event (d_DEE_RevieveEvent)
  Serial.begin(9600);                         // start serial for output
  Serial.print("DEBUG_ENABLED MODE IS ");
  if(DEBUG_ENABLED) Serial.println("ON");
  else Serial.println("OFF");
   int countdownMS = Watchdog.enable(8000);
}
