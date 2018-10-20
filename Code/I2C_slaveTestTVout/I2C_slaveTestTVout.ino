#include <TVout.h>
#include <utility/fontALL.h>
#include <Wire.h>

TVout TV;
unsigned char x,y;
String text;
int index = 0;

char text2[14];
void setup()  {
  Wire.begin(8);// join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  TV.begin(NTSC);	//for devices with only 1k sram(m168) use TV.begin(_NTSC,128,56)
  TV.select_font(font6x8);
  Serial.begin(9600);
}
void loop() {
  TV.clear_screen();
  TV.println(text2);
  TV.delay(100);
  delay(50);
  Serial.println("loop");

}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.println(c);
    text = text + c;
    index++;
    if (index == 14) {
      text = "";
      index = 0;
    }
    }
    text.toCharArray(text2, 14);
  }
