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
    HapticController(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6);
    void update(int flex1, int flex2, int flex3);
  private:
    int _pin1;
    int _pin2;
    int _pin3;
    int _pin4;
    int _pin5;
    int _pin6;
    unsigned long _previousMillis;
    void pattern1(int pin1, int pin2);
};

#endif
