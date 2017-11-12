#include "FlexSensor.h"
#include "HapticController.h"

FlexSensor flex1(13);
HapticController hapticController(1,2,3,4,5,6);

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  flex1.read();
  hapticController.update(101,1,101);
}
