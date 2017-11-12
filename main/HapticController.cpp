/*
 * HapticController.h - Library for controlling haptic units
 * Created by Geoffrey van Driessel, November 11, 2017.
 */
#include "Arduino.h"
#include "HapticController.h"

HapticController::HapticController(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6)
{
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  _pin1 = pin1;
  _pin2 = pin2;
  _pin3 = pin3;
  _pin4 = pin4;
  _pin5 = pin5;
  _pin6 = pin6;
  _previousMillis = millis();  
}

void HapticController::update(int flex1, int flex2, int flex3)
{
  int pattern1Threshhold = 100;
  if(flex1 > pattern1Threshhold){
    pattern1(_pin1, _pin2);
  }
  if(flex2 > pattern1Threshhold){
    pattern1(_pin3, _pin4);
  }
  if(flex3 > pattern1Threshhold){
    pattern1(_pin5, _pin6);
  }
}

void HapticController::pattern1(int pin1, int pin2){
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
}

