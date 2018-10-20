#include<Wire.h>
#include<Process.h>
#define motherboard_addr 8  // I2C address
#define keyboard_addr 9
#define graphics_addr 10

String curCommand = "";
bool output_graphics = false;







void setup() {
  Bridge.begin();
  SerialUSB.begin(9600);
  Wire.begin(motherboard_addr);
  Wire.onReceive(recieve_KeyboardInput);    // register event
  // Serial.begin(9600); ??

}

int x = 0;
void loop() {

  
                    //Read Keyboard Inputs

  if (output_graphics) {
    Wire.beginTransmission(graphics_addr); // transmit to device #9
    Wire.write("slave_x is ");        // sends five bytes
    Wire.write(x);              // sends one byte
    Wire.endTransmission();    // stop transmitting
  
    //x++;
  }

                    //Send typed info to monitor






                    //If enter has been pressed, run command







                    //If command has been run, send return values to monitor

}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void recieve_KeyboardInput(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  x = Wire.read();            // receive byte as an integer
  Serial.println(x);         // print the integer
}

