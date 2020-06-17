//  Demo function:The application method to drive the DC motor.
//  Author:Loovee (luweicong@seeed.cc)
//  2016-3-11

#include "MotorDriver.h"

MotorDriver motor;

 #define outputA 6
 #define outputB 7
 #define motorPin 10
 int counter = 0; 
 int stateA, stateB;
 int initStateA, initStateB;  
 void setup() { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   motor.begin();
   
   Serial.begin (9600);
   // Reads the initial state of the outputA
   initStateA = digitalRead(outputA);   
   initStateB = digitalRead(outputB);

   Serial.print("Posicao inicial A: ");
   Serial.print(initStateA);
   Serial.print("\n");

   Serial.print("Posicao inicial B: ");
   Serial.print(initStateB);
   Serial.print("\n");
 } 

void loop() {
    //motor.speed(0, 100);            // set motor0 to speed 100
    /*delay(1000);
    motor.brake(0);                 // brake
    delay(1000);
    motor.speed(0, -100);           // set motor0 to speed -100
    delay(1000);
    motor.stop(0);                  // stop
    delay(1000);
    */

   stateA = initStateA;
   stateB = initStateB;
   if (initStateA == initStateB){
    while (stateA == stateB){
      motor.speed(0, 80);
      stateA = digitalRead(outputA);
      stateB = digitalRead(outputB);
    }
    motor.speed(0, 0);
    Serial.print("Posicao final A: ");
    Serial.print(stateA);
    Serial.print("\n");
  
    Serial.print("Posicao final B: ");
    Serial.print(stateB);
    Serial.print("\n");
   }
   else {
    while (stateA != stateB){
      motor.speed(0, 80);
      stateA = digitalRead(outputA);
      stateB = digitalRead(outputB);
    }
    motor.speed(0, 0);
    Serial.print("Posicao final A: ");
    Serial.print(stateA);
    Serial.print("\n");

    Serial.print("Posicao final B: ");
    Serial.print(stateB);
    Serial.print("\n");
   }
}
// END FILE
