#include <Wire.h>    //I2C library
#define master_addr 9
#define slave_addr 8

void setup() {
  Wire.begin(master_addr);
  Serial.begin(9600);

  Wire.onReceive(receiveEvent); // register event
}
int x = 0;

void loop() {
  Wire.beginTransmission(slave_addr); // transmit to device #8
  Wire.write("master_x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting

  x++;
  delay(500);
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}
