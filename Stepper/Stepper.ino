/*
  Code 1 
  Board: ULN2003 Driver & 28BYJ-48 Stepper Motor & Arduino Uno IDE 1.8.5
  Connections:  See Fritzing in https://medium.com/jungletronics/28byj-48-stepper-motor-peak-rpm-658eae6afe2f 
  Power Supply: 12v .5A or 5v .5A USB Power Cable right into 5.5mm Jack of UL2003 Board
  Max RPM:      Power Supply 5v .5A USB -> #define waiting_time 2 (seconds) MAX 14.5 RPM
                Power Supply 9v .5A     -> #define waiting_time 1 (seconds) MAX 29.0 RPM
                                            but heat issue happens:/    
 */


#define stepper PORTB
#define waiting_time 2 // or 2 change here!

void setup() {
  
  for (int z = 8; z < 12; z++) {  // FULL STEP DRIVE
    pinMode(z, OUTPUT);           // pins 8,9,10,11 output for driving the motor

  }
}

void loop() {

  stepper = 0B0011;               // 0x03;

  delay(waiting_time);

  stepper = 0B0110;               // 0x06;

  delay(waiting_time);

  stepper = 0B1100;               // 0x0C;

  delay(waiting_time);
  stepper = 0B1001;               // 0x09;

  delay(waiting_time);

}
