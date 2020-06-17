/*     Arduino Rotary Encoder Tutorial
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
 
 #define outputA 6
 #define outputB 7
 #define motorPin 2
 int counter = 0; 
 int stateA, stateB;
 int initStateA, initStateB;  
 void setup() { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   
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
   initStateA = digitalRead(outputA);   
   initStateB = digitalRead(outputB);

   Serial.print("A: ");
   Serial.print(initStateA);
   Serial.print("\n");

   Serial.print("B: ");
   Serial.print(initStateB);
   Serial.print("\n");

   delay(1000);
 }
