#define ENCODER_USE_INTERRUPTS
#include <Encoder.h>

Encoder eixoX(2, 3);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("GO");
}

long positionLeft  = -999;

void loop() {
  // put your main code here, to run repeatedly:

  long newLeft, newRight;
  newLeft = eixoX.read();

  if (newLeft != positionLeft) {
    Serial.print("Left = ");
    Serial.print(newLeft);

    Serial.println();
    positionLeft = newLeft;

  }
}
