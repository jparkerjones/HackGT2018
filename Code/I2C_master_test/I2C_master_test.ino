#include <Wire.h>    //I2C library

char a = 'A';
int b = 0;
void setup() {
  Wire.begin();
  Serial.begin(9600);

}

void loop() {
  
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("A");        // sends 1 byte
  //if (b == 6){
    //Wire.write("\n");     //every 6 characters send newline
    //b = 0;
  //}
  Wire.endTransmission();    // stop transmitting
  Serial.println("Sent:");
  delay(500);
  //a = char(a + 1);
  //if(a>'Z') {
    //a = 'A';
  //}
  //b++;

}
