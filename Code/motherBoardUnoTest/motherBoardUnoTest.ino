#include<Wire.h>
//#include<Process.h>
#define motherboard_addr 8  // I2C address
#define keyboard_addr 9
#define graphics_addr 10

String curCommand = "";
bool output_graphics = false;


int counter = 0;

void setup() {
  //Bridge.begin();
  //SerialUSB.begin(9600); 
  
  Wire.begin(motherboard_addr);
  Wire.onReceive(receive_KeyboardEvent);    // register event
  Serial.begin(9600);

}

int x;
void loop() {
  //Read Keyboard Inputs


  //Send typed info to monitor
  if (output_graphics) {
    if (counter == 0) {
    Wire.beginTransmission(graphics_addr); // transmit to device #10
    Wire.write("motherboard_x is ");        // sends five bytes
    Wire.write(x);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    counter++;
    }
    else if (counter == 1) {
      Wire.beginTransmission(graphics_addr); // transmit to device #10
      Wire.write("ITS TIME TO stop");        // sends five bytes
      Wire.write(x);              // sends one byte
      Wire.endTransmission();    // stop transmitting
      counter = 0;
      
      
    }
  
    //x++;
    output_graphics = false;
  }

  //If enter has been pressed, run command

  //If command has been run, send return values to monitor
  
  delay(500);
  output_graphics = true;
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receive_KeyboardEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  x = Wire.read();            // receive byte as an integer
  Serial.println(x);         // print the integer
}
