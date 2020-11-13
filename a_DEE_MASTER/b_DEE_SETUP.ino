//THE SETUP FUNCTION

void setup() {
  Serial.begin(9600); //Begin the Serial
  Serial.print("SETUP, DEBUG_MODE IS");
  if(DEBUG_ENABLED) Serial.println(" ON");
  else Serial.println(" OFF");
  initI2C(); // Initialize I2C communication (in e_DEE_I2C)
  initSDCard(); // Initialize the SD card  (in f_DEE_SD_CARD)
  getSDCardInfo(); // Retrieve tha last visited page (currPage value)
  delay(1000); 
  setupEthernet(); // Setup the etherner shield (in d_DEE_ETHERNER)
  delay(1000);
}
