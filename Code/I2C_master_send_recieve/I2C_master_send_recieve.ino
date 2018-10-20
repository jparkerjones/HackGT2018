#include <Wire.h>

bool reading = false;
void setup() {
  Wire.begin(9);        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  // act like a slave, send data
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  if (reading) {
    Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8

    while (Wire.available()) { // slave may send less than requested
      char c = Wire.read(); // receive a byte as character
      Serial.print(c);         // print the character
    }
    reading = false;
  } else {
    
    reading = true;
  }

  delay(500);
}

void requestEvent() {
  Wire.write("I am your master\n");
}

