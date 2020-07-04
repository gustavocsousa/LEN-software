int initState;

void setup(){
  pinMode(12, INPUT);

  Serial.begin(9600);
  Serial.setTimeout(10);

  initState = digitalRead(12);

  Serial.print("First condition of encoder: ");
  Serial.println(initState);
}

void loop(){
  int updatePin = digitalRead(12);
  if (updatePin != initState){
    Serial.println("Change");
    initState = updatePin;
  }
}
