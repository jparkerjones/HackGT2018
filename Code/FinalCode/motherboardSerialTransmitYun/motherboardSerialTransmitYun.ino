#include<Wire.h>
#include<Process.h>
#include<Console.h>
#define motherboard_addr 8  // I2C address
#define keyboard_addr 9
#define graphics_addr 10

String curCommand = "";
bool output_graphics = false;
char inByte = 0;


int counter = 0;

void setup() {
  Bridge.begin();
  Console.begin();
  while(!Console);
  
  
  Wire.begin(motherboard_addr);
  Wire.onReceive(receive_KeyboardEvent);    // register event

}

int x;
void loop() {
  //Read Keyboard Inputs
  inByte =0;
  while (inByte==0){
  if (Console.available() > 0) {
    // get incoming byte:
    inByte = Console.read();
    Console.println(inByte);
    }
  }
  Wire.beginTransmission(graphics_addr); // transmit to device #10
    Wire.write(inByte);        // sends five bytes
    //Wire.write(x);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    counter= 1;
    Console.println("transmitted a");
  
  delay(50);
  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receive_KeyboardEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Console.print(c);         // print the character
  }
  x = Wire.read();            // receive byte as an integer
  Console.println(x);         // print the integer
}
