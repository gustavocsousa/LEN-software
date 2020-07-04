#include <CheapStepper.h>

CheapStepper stepper;

int port = 0, integerValue = 0, incomingByte;

boolean moveClockwise = true;

void setup() {

  //stepper.setRpm(20);
/*
  for (int z = 8; z < 12; z++) {  // FULL STEP DRIVE
    pinMode(z, OUTPUT);           // pins 8,9,10,11 output for driving the motor
  }
*/
  Serial.begin(9600);
  Serial.println("Ready to start moving!");

}

void loop() {

  moveClockwise = false ;

  integerValue = 0;

  if (Serial.available() > 0) {
      integerValue = 0;
      while(1) {
        incomingByte = Serial.read();
        if (incomingByte == '\n') break;
        if (incomingByte == -1) continue;
        integerValue *= 10;
        integerValue = ((incomingByte - 48) + integerValue);
      }
  }

  for (int i = 0; i < integerValue; i++){
    stepValue();
  }

}

void stepValue(){

  stepper.step (moveClockwise);

}
