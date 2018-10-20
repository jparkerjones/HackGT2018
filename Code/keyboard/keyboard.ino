#include <Wire.h>    //I2C library
#define motherboard_addr 8  // I2C address
#define keyboard_addr 9
#define graphics_addr 10

void setup() {
  Wire.begin(keyboard_addr);
  Serial.begin(9600);
}

byte x = 0;

void loop() {
  Wire.beginTransmission(motherboard_addr);   // transmit to device #8
  Wire.write("keyboard is ");           // sends five bytes
  Wire.write(x);                        // sends one byte
  Wire.endTransmission();               // stop transmitting
  Serial.print(x);
  x++;
  delay(500);
}
