#include <Wire.h>
String data = "Bonnes vacances a tous!";
String data2 ="et heureuse annee !";
String dataEnd = "X";

void setup()
{
  Wire.begin();                

}

void loop()
{
  delay(5000);
  sendMessage();
}

void sendMessage()
{
   Serial.println("Sending message");
  Wire.beginTransmission(2);
  Wire.write(data.c_str());
  Wire.endTransmission();
  
  Wire.beginTransmission(2);
  Wire.write(data2.c_str());
  Wire.endTransmission(); 

  Wire.beginTransmission(2);
  Wire.write(dataEnd.c_str());
  Wire.endTransmission();
                   
  delay(500);
}
