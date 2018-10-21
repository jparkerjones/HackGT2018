#include<Wire.h>
//#include<Process.h>
#define motherboard_addr 8  // I2C address
#define keyboard_addr 9
#define graphics_addr 10

String curCommand = "";
bool output_graphics = false;
char inByte = 0;


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
  inByte =0;
  while (inByte==0){
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    Serial.println(inByte);
    }
  }
  Wire.beginTransmission(graphics_addr); // transmit to device #10
    Wire.write(inByte);        // sends five bytes
    //Wire.write(x);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    counter= 1;
    Serial.println("transmitted a");
  
  delay(50);
  
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
