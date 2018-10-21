#include <Wire.h>    //I2C library
#define motherboard_addr 8  // I2C address
#define keyboard_addr 9
#define graphics_addr 10

// assign pin numbers
int top_m1 = 13;
int top_m1_c1 = 12;
int top_m1_c0 = 11;

int top_m2 = 10;
int top_m2_c1 = 9;
int top_m2_c0 = 8;

int bottom_c1 = 7;
int bottom_c0 = 6;
int bottom_m3 = 5;
int bottom_m4 = 4;
int bottom_m5 = 3;
int bottom_m6 = 2;

int key_map_matrix[8][16] = {
 {0, 0, 0, 27, 0, 71, 0, 72, 0, 0, 0, 0, 8, 0, 39, 0},
 {0, 0, 87, 81, 69, 82, 0, 85, 73, 0, 0, 0, 0, 79, 80},
 {0, 0, 50, 49, 51, 52, 0, 54, 55, 0, 0, 0, 0, 57, 48, 0},
 {0, 0, 83, 65, 68, 70, 0, 74, 75, 0, 0, 0, 0, 76, 59, 0},
 {0, 0, 88, 90, 67, 86, 0, 77, 60, 0, 0, 0, 32, 62, 47, 0},
 {0, 0, 0, 9, 0, 84, 0, 89, 74, 0, 0, 0, 0, 0, 91, 0},
 {0, 0, 0, 0, 0, 66, 0, 78, 0, 0, 0, 0, 0, 0, 61, 127}
 }; // [top_wire][bottom_wire] = ASCII value of key_pressed

void setup() {
  Wire.begin(keyboard_addr);
  Serial.begin(9600);

  for (int i = 13; i >= 6; i--) {
    pinMode(i, OUTPUT);
  }

  for (int i = 5; i >= 2; i--) {
    pinMode(i, INPUT);
  }

}

byte x = 0;

void loop() {
  int key_pressed = decode_key();
  if (key_pressed != 0) {
    Wire.beginTransmission(motherboard_addr);   // transmit to device #8
    Wire.write("keyboard is ");           // sends five bytes
    Wire.write(x);                        // sends one byte
    Wire.endTransmission();               // stop transmitting
    Serial.print(x);
    x++;
  }
  
  delay(500);
}

int decode_key() {
  
  for (int m = 0; m <= 1; m++) { // check both mux
    if (m == 0) {
      digitalWrite(top_m1, HIGH); // check mux1 input
      digitalWrite(top_m2, LOW);
    } else {
      digitalWrite(top_m1, LOW);  // check mux2 input
      digitalWrite(top_m2, HIGH);
    }
    
    for (int i = 0; i < 4; i++) {     // set out2 - out5 high one at a time
      if (m == 0) {
        digitalWrite(top_m1_c1, i/2);
        digitalWrite(top_m1_c0, i%2);
      } else {
        digitalWrite(top_m2_c1, i/2);
        digitalWrite(top_m2_c0, i%2);
      }
      
  
      for (int c = 0; c < 4; c++) {   // set the control signals for bottom layer
        digitalWrite(bottom_c1, i/2);
        digitalWrite(bottom_c0, i%2);
  
        if (digitalRead(bottom_m3)) { // something is connected to M3 
          switch (c){
            case 0: // out4
              return key_map_matrix[i + 4 * m][0];
            case 1: // out7
              return key_map_matrix[i + 4 * m][1];
            case 2: // out10
              return key_map_matrix[i + 4 * m][2];
            case 3: // out11
              return key_map_matrix[i + 4 * m][3];
          }
        }
  
         if (digitalRead(bottom_m4)) { // something is connected to M4 
          switch (c) {
            case 0: // out13
              return key_map_matrix[i + 4 * m][4];
            case 1: // out14
              return key_map_matrix[i + 4 * m][5];
            case 2: // out15
              return key_map_matrix[i + 4 * m][6];
            case 3: // out16
              return key_map_matrix[i + 4 * m][7];
          }
        }
  
         if (digitalRead(bottom_m5)) { // something is connected to M5
          switch (c){
            case 0: // out17
              return key_map_matrix[i + 4 * m][8];
            case 1: // out18
              return key_map_matrix[i + 4 * m][9];
            case 2: // out19
              return key_map_matrix[i + 4 * m][10];
            case 3: // out20
              return key_map_matrix[i + 4 * m][11];
           }
        }
  
         if (digitalRead(bottom_m6)) { // something is connected to M6 
          switch (c){
            case 0: // out21
              return key_map_matrix[i + 4 * m][12];
            case 1: // out22
              return key_map_matrix[i + 4 * m][13];
            case 2: // out23
              return key_map_matrix[i + 4 * m][14];
            case 3: // out24
              return key_map_matrix[i + 4 * m][15];
          }
        }
      }
    }
  }
  
  return 0;
}

