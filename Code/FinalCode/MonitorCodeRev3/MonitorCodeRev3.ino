#include <Wire.h>
#include <TVout.h>
#include <utility/fontALL.h>

TVout TV;


#define motherboard_addr 8  // I2C address
#define keyboard_addr 9
#define graphics_addr 10



char line1[15] = "";
char line2[15] = "";
char line3[15]= "";
char line4[15] = "";
char line5[15] = "";
char line6[15]= "";
char lineClr[15] = "";

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
  TV.println("My terminal: (ツ)");
  TV.println(line6);
  TV.println(line5);
  TV.println(line4);
  TV.println(line3);
  TV.println(line2);
  TV.println(line1);
  TV.delay(50);  

  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receive_Motherboard_Event(int howMany) {     //add sent chars to line
  while (0 < Wire.available()) { // loop through all
    char c  = Wire.read(); // receive byte as a character

    if (c == '|') {
        moveRow(line6, line5);
        moveRow(line5, line4);
        moveRow(line4, line3);
        moveRow(line3, line2);
        moveRow(line2, line1);
        moveRow(line1, lineClr);
        curIndex = 0;
        Serial.println("lines shifted");
      
    } else {


   
    line1[curIndex] = char(c);
    Serial.println("character added to line1");
    curIndex++;
    }
    if (curIndex==30){
    curIndex = 0;
    }
    
 
  }
 }
void moveRow(char arrolder[15], char arrnewer[15]){
  for (int i = 0; i<15; i++) {
          arrolder[i] = arrnewer[i];
        }
}
