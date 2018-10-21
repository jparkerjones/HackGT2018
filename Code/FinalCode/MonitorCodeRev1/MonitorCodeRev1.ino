#include <Wire.h>
#include <TVout.h>
#include <utility/fontALL.h>

TVout TV;


#define motherboard_addr 8  // I2C address
#define keyboard_addr 9
#define graphics_addr 10



char text[40];
int curIndex = 0;


void setup() {
  Wire.begin(graphics_addr);          // join i2c bus 
  Wire.onReceive(receive_Motherboard_Event);       // register event
  Serial.begin(9600);// start serial for output
  TV.begin(NTSC);  //for devices with only 1k sram(m168) use TV.begin(_NTSC,128,56)
  TV.select_font(font6x8);
}

void loop() {
  TV.clear_screen();
  TV.println("hello there");
  TV.println(text);
  TV.delay(100);
  //text[curIndex] = char('a');
  //curIndex++;
  

  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receive_Motherboard_Event(int howMany) {
  while (0 < Wire.available()) { // loop through all
    char c  = Wire.read(); // receive byte as a character
    Serial.println(c);
    text[curIndex] = char(c);
    curIndex++;
    if (curIndex==40){
    curIndex = 0;
  }
    
 
  }
  }
