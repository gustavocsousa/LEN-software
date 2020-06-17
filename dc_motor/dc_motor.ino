#define in1 6
#define in2 7
void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  // Set initial rotation direction
}
void loop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(50);
  digitalWrite(in2, LOW);
  delay(1000);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(50);
  digitalWrite(in1, LOW);
  delay(1000);
}
