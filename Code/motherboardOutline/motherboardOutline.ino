#include<Wire.h>
#include<Process.h>


int keyboardID = 10;    //I2C addresses
int monitorID = 9;



String curCommand = "";








void setup() {
  Bridge.begin();
  SerialUSB.begin(9600);

}

void loop() {

  
                    //Read Keyboard Inputs




                    //Send typed info to monitor






                    //If enter has been pressed, run command







                    //If command has been run, send return values to monitor

}
