//THE SETUP FUNCTION

void setup() {
  Wire.begin(SLAVE_ID);                       // join i2c bus with address
  Wire.onReceive(receiveEvent);               // register event (d_DEE_RevieveEvent)
  Serial.begin(9600);                         // start serial for output
  Serial.print("DEBUG_ENABLED MODE IS ");
  if(DEBUG_ENABLED) Serial.println("ON");
  else Serial.println("OFF");
}
