#include "Servo.h"

// Pin Definitions
#define SERVOMD_PIN_SIG  2
int led = 13;
Servo servoMD;

void setup() {
  Serial.begin(9600);
  while (!Serial) ;
  pinMode(led, OUTPUT); 
  servoMD.attach(SERVOMD_PIN_SIG);
}

void loop() {
    int ints[3];
    int i=0;
    int data = 0;
    if(Serial.available()){
      while ((data = Serial.read()) != "\0" || i>=3){
        ints[i++] = data; 
      } 
    }
    if(i==1){
      servoMD.write(ints[0]);
    }
    else if(i==2){
      servoMD.write(ints[0]*10+ints[1]);
    }else if(i==3){
      servoMD.write(ints[0]*100+ints[1]*10+ints[2]);
    }
    delay(500);
} 
