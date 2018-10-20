
#include <Wire.h>

unsigned char x,y;
String text;
int index = 0;

//char text2[14];
void setup()  {
  Wire.begin(8);// join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  
  Serial.begin(9600);
}
void loop() {
  
  delay(50);
  Serial.println("Test:");
  Serial.println(text);
  

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
    //text.toCharArray(text2, 14);
  }
