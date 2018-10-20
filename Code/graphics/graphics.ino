#include <Wire.h>
#define motherboard_addr 8  // I2C address
#define keyboard_addr 9
#define graphics_addr 10

void setup() {
  Wire.begin(graphics_addr);          // join i2c bus 
  Wire.onReceive(receive_Motherboard_Event);       // register event
  Serial.begin(9600);                 // start serial for output
}

void loop() {
  delay(500);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receive_Motherboard_Event(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}
