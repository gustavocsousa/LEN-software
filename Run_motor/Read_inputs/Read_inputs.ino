int motorPin = 10;

void setup() {
  Serial.begin(57600);
  
  pinMode(A0, INPUT);

  pinMode(A1, INPUT);
 
  pinMode(motorPin, OUTPUT);

  digitalWrite(motorPin, HIGH);

  Serial.print("Inicializando...\n");

}

void loop() {
  int valor = analogRead(A0);

  int valor2 = analogRead(A1);


  Serial.print("Valor A0: ");
  Serial.print(valor);
  Serial.print("\n");

  Serial.print("Valor A1: ");
  Serial.print(valor2);
  Serial.print("\n");

  Serial.print("\n");

  delay(1000);

}
