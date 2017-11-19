/*
 * HapticController.h - Library for controlling haptic units
 * Created by Geoffrey van Driessel, November 11, 2017.
 */
#ifndef HapticController_h
#define HapticController_h

#include "Arduino.h"

class HapticController
{
public:
HapticController(int pinArray[]);
void update(float flex1, float flex2, float flex3);
private:
int _pin1;
int _pin2;
int _pin3;
int _pin4;
int _pin5;
int _pin6;
unsigned long _previousMillis;
void pattern1(float flex, int pin1, int pin2);
};

#endif
