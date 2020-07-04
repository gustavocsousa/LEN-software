volatile unsigned long encoderPos = 0;
int motor_value = 160;
unsigned int integerValue=0;  // Max value is 65535
int incomingByte;
int initState;
volatile bool STOP = false;
int motorDelay = 10;

void setup(){

  Serial.begin(9600);
  Serial.setTimeout(10);
  pinMode(2, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  initState = digitalRead(2);

  Serial.print("First condition of encoder: ");
  Serial.println(initState);

  attachInterrupt(digitalPinToInterrupt(2), encoder, CHANGE);


}

void loop(){
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
    delay(4);
    //delay(motorDelay);
/*
    while(encoder_pos != i){

      if (encoder_pos > i) i++;

      else{
        for(int j = 0; j < i - encoder_pos; j++){
          stepValue();
        }
      }

    }
*/
  }

  delay (1000);

  Serial.println(encoderPos);

}

void stepValue(){

  while(!STOP){

  analogWrite(6, motor_value);
  digitalWrite(5, LOW);

  }

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

  STOP = false;
}

void encoder(){
  STOP = true;
  encoderPos++;
}
