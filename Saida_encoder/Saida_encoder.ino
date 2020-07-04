volatile long int encoder_pos = 0;
int motor_value = 255;
unsigned int integerValue=0;  // Max value is 65535
int incomingByte;
int initState, state;
bool stateFlag = false;
bool STOP = false;
int motorDelay = 10;

void setup() {

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



void loop() {
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

  if (integerValue!=0){
    Serial.print("Valor recebido: ");
    Serial.println(integerValue);
  }

//satetFlag true significa que é para rodar no sentido antihorário, somando a posição do encoder

  if(integerValue > 0){
    stateFlag = true;
    MotorCounterClockwise(motor_value);
  }
    delay(10);

}


void encoder(){
  if (encoder_pos != 0) Serial.println(encoder_pos);
  if (stateFlag) encoder_pos++;
  else encoder_pos--;
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  encoder_pos == integerValue ? STOP = true : STOP = false;
}

void MotorClockwise(int power){
  while(1){
    analogWrite(5, power);
    digitalWrite(6, LOW);
    if (STOP) break;
  }
  STOP = false;
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

void MotorCounterClockwise(int power){
   while(1){
    //Serial.println(encoder_pos);
    analogWrite(6, power);
    digitalWrite(5, LOW);
    if (STOP) break;
  }
  STOP = false;
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}
