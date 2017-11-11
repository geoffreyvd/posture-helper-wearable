/*
 * FlexSensor.h - Library for using flex sensors
 * Created by Geoffrey van Driessel, November 11, 2017.
 */
#include "Arduino.h"
#include "Morse.h"

FlexSensor::FlexSensor(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
}

float FlexSensor::read()
{
  return analogRead(_pin);
}