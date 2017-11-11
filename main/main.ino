#include "FlexSensor.h"

FlexSensor flex1(13);

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  flex1.read();
}
