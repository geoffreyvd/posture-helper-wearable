/*
 * HapticController.h - Library for controlling haptic units
 * Created by Geoffrey van Driessel, November 11, 2017.
 */
#ifndef HapticController_h
#define HapticController_h

#include "Arduino.h"
#include "FlexSensor.h"

class HapticController
{
public:
HapticController(int pinArray[], int pattern, FlexSensor &flex1, FlexSensor &flex2, FlexSensor &flex3);
void update();
private:
int _pin1;
int _pin2;
int _pin3;
FlexSensor _flex1;
FlexSensor _flex2;
FlexSensor _flex3;
int _selectedPattern;
int _highToLowIntensity;
int _lowToHighIntensity;
int _patternPulseDelay;
unsigned long _previousMillis;
unsigned long _patternTimer;
void pattern1(FlexSensor flex, int pin, int amplifier);
void pattern2(FlexSensor flex, int pin);
void pattern3(FlexSensor flex, int pin);
};

#endif
