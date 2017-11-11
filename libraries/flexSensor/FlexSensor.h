/*
 * FlexSensor.h - Library for using flex sensors
 * Created by Geoffrey van Driessel, November 11, 2017.
 */
#ifndef FlexSensor_h
#define FlexSensor_h

#include "Arduino.h"

Class FlexSensor
{
  public:
    FlexSensor(int pin);
    float read();
  private:
    int _pin;
}

#endif
