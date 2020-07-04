//Include the libraries we need
#include <PinChangeInterrupt.h>
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>
#include <TimerOne.h>                          // Timer one interrupts

//////////////////////////////////////////////////////////////
/////////////////////DEFINE PID constants/////////////////////
//////////////////////////////////////////////////////////////
int kp = 2, ki = 0.01, kd = 0.02;
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

int input, output, setpoint;
int iTerm = 0, lastInput = 0, dInput = 0, error = 0;
int outMin = -255, outMax = 255;
int sampleTime = 10;                                //This values is is milliseconds
volatile long encoderPos = 0;
bool direction = false;
int incomingByte;
int integerValue;

//////////////////////////////////////////////////////////////
////////////////////Define the pins we use////////////////////
//////////////////////////////////////////////////////////////
#define Encoder_A      2                                    // Quadrature encoder A pin
#define Motor_CW       5                                  // PWM outputs to L298N H bridge motor driver module
#define Motor_CCW      6

void setup(void)
{
  pinMode(Encoder_A, INPUT);                                // quadrature encoder input A
  attachPCINT(digitalPinToPCINT(Encoder_A), encoder, CHANGE);  // We update encoder position each falling edge detected in the interrumption
  TCCR2B = TCCR2B & 0b11111000 | 1;                             // set 31Kh PWM to prevent motor whine (timer 2)
  Timer1.initialize(sampleTime * 1000);                         // setup timer 1
  Timer1.attachInterrupt(Compute);
  Serial.begin(9600);                                         //Just for debugging if you want to print values
  /*
  while(digitalRead(END_stop))
  {
    analogWrite(Motor_CW, 0);                                   // Rotate the motor CCW
    analogWrite(Motor_CCW, 255);
  }
  analogWrite(Motor_CW, 0);                                     // Stop the motor
  analogWrite(Motor_CCW, 0);
  */
}

void Compute()
{
  setpoint = integerValue;            // setpoint position is made with a potentiometer but could be given by serial monitor or other...
  input = encoderPos;                                           // we get the data from the encoder interrumption
  error = setpoint - input;
  iTerm += ki * error * sampleTime;
  if (iTerm > outMax) iTerm = outMax;                           // prevent that the I term from PID gets too big
  else if (iTerm < outMin) iTerm = outMin;
  dInput = (input - lastInput) / sampleTime;
  output = kp * error + iTerm - kd * dInput;                    // The PID output is the sum of P I and D values
  if (output > outMax) output = outMax;                         // limit output to 0 and 255 for the analog write
  else if (output < outMin) output = outMin;
  lastInput = input;                                            //Remember to save the last input value for the next loop
  pwmOut(output);                                               //Change the analog write for the motor control
}

void pwmOut(int out) {                                          // to H-Bridge board
  if (out > 0) {
    direction = false;
    analogWrite(Motor_CW, out);                                 // Rotate the motor CW
    analogWrite(Motor_CCW, 0);
  }
  else {
    direction = true;
    analogWrite(Motor_CW, 0);
    analogWrite(Motor_CCW, abs(out));                           // Rotate the motor CCW
  }
}

void encoder()  {                                     // pulse and direction, direct port reading to save cycles
  if (direction) encoderPos++;
  else encoderPos--;
}

void loop(void)
{
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

  if (integerValue != 0) Compute(integerValue);

}
