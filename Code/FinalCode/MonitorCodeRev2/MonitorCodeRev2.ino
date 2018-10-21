#include <Wire.h>
#include <TVout.h>
#include <utility/fontALL.h>

TVout TV;


#define motherboard_addr 8  // I2C address
#define keyboard_addr 9
#define graphics_addr 10



char line1[30];
char line2[30];
char line3[30];
char line4[30];
char line5[30];
char line6[30];

char *pl1 = &line1[0];
char *pl2= &line2[0];
char *pl3 = &line3[0];
char *pl4 = &line4[0];
char *pl5= &line5[0];
char *pl6 = &line6[0];


//char spaces[30] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
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
  TV.delay(100);
  

  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receive_Motherboard_Event(int howMany) {     //add sent chars to line
  while (0 < Wire.available()) { // loop through all
    char c  = Wire.read(); // receive byte as a character

    if (c == '\n') {
        moveRow(pl6, pl5);
        moveRow(pl5, pl4);
        moveRow(pl4, pl3);
        moveRow(pl3, pl2);
        moveRow(pl2, pl1);
        curIndex = 0;
      
    } else {


   
    line1[curIndex] = char(c);
    curIndex++;
    }
    if (curIndex==30){
    curIndex = 0;
    }
    
 
  }
 }
void moveRow(char *placeholder1, char *placeholder2){
  for (int i = 0; i<30; i++) {
          placeholder1 = *placeholder2;
          placeholder1++;
          placeholder2++; 
        }
}
