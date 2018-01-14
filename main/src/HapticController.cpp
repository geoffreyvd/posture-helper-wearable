/*
* HapticController.h - Library for controlling haptic units
* Created by Geoffrey van Driessel, November 11, 2017.
*/
#include "Arduino.h"
#include "HapticController.h"
#include "FlexSensor.h"

/**
* [HapticController::HapticController description]
* @param pin1 [description]
* @param pin2 [description]
* @param pin3 [description]
* @param pin4 [description]
* @param pin5 [description]
* @param pin6 [description]
*/
HapticController::HapticController(int pinArray[], int pattern, FlexSensor *flex1, FlexSensor *flex2, FlexSensor *flex3)
{
  for (int i=0; i<3; i++) {
    pinMode(pinArray[i], OUTPUT);
  }
  _pin1 = pinArray[0];
  _pin2 = pinArray[1];
  _pin3 = pinArray[2];
  _selectedPattern = pattern;
  _flex1 = flex1;
  _flex2 = flex2;
  _flex3 = flex3;
  _patternTimer = 0;
  _lowToHighIntensity = 0;
  _highToLowIntensity = 255;
  _patternPulseDelay = 100;
  _upperTriggered = false;
  _middleTriggered = false;
  _lowerTriggered= false;
  _upperCounter = 0;
  _lowerCounter = 0;
  _middleCounter = 0;
}

/**
*
* @param flex1 Amount of resistance for 1st FlexSensor
* @param flex2 Amount of resistance for 2nd FlexSensor
* @param flex3 Amount of resistance for 3rd FlexSensor
*/
void HapticController::update()
{

  if (_selectedPattern == 1)
  {
    pattern1(_flex1, _pin1, 100);
    pattern1(_flex2, _pin2, 100);
    pattern1(_flex3, _pin3, 100);

  } else if(_selectedPattern == 2){

    pattern2(_flex1, _flex2, _flex3);

  } else if(_selectedPattern == 3){

    pattern3(_flex1, _pin1);
    pattern3(_flex2, _pin2);
    pattern3(_flex3, _pin3);

  } else if(_selectedPattern == 4) {

    pattern4(_pin1);
    pattern4(_pin2);
    pattern4(_pin3);

  }
}

/**
* [HapticController::pattern1 Use PWM to adjust the intensity of haptic vibration based on the angle of the flex sensor]
*/
void HapticController::pattern1(FlexSensor *flex, int pin, int amplifier){
  int intensity = flex->getValue();
  bool trigger = false;
  //Serial.println("intensity: " + String(pin) +  " " + String(intensity));
  if(intensity > 20 || intensity < -20) {
    trigger = true;
  }


  //assume that value is given between -180 and +80, make negative postive so it can be used to map intensity
  if(trigger) {
    if(intensity > 0){
      intensity = intensity * -1;
    }

    intensity = (intensity * amplifier) / 100;

    intensity = constrain(map(intensity, 0, flex->_maximumValueCalibrated, 0, 255), 0, 255);


    analogWrite(pin, intensity);
  } else {
    analogWrite(pin, 0);
  }

}

void HapticController::pattern2(FlexSensor *flex1, FlexSensor *flex2, FlexSensor *flex3 ) {

  unsigned long currentTime = millis();
  int flexValue1 = flex1->getValue();
  int flexValue2 = flex2->getValue();
  int flexValue3 = flex3->getValue();

  int lowerBound = -35;
  int upperBound = 35;

  if(flexValue1 < lowerBound || flexValue1 > upperBound) {
    _upperCounter++;
    if(_upperCounter == 3) {
      _upperTriggered = true;
      _upperCounter--;
    }
  } else {
    if(_upperCounter > 0) {
      _upperCounter--;
    } else {
      _upperTriggered = false;
    }
  }

  if(flexValue2 < lowerBound || flexValue2 > upperBound) {
    _middleCounter++;
    if(_middleCounter == 3) {
      _middleTriggered = true;
      _middleCounter--;
    }
  } else {
    if(_middleCounter > 0) {
      _middleCounter--;
    } else {
      _middleTriggered = false;
    }
  }

  if(flexValue3 < lowerBound || flexValue3 > upperBound) {
    _lowerCounter++;
    if(_lowerCounter == 3) {
      _lowerTriggered = true;
      _lowerCounter--;
    }
  } else {
    if(_lowerCounter > 0) {
      _lowerCounter --;
    } else {
      _lowerTriggered = false;
    }
  }


  if( currentTime > _patternTimer + _patternPulseDelay) {

    if(_upperTriggered == true) {
      analogWrite(_pin1, _lowToHighIntensity);
    } else {
      analogWrite(_pin1, 0);
    }

    if(_middleTriggered == true) {
      analogWrite(_pin2, _lowToHighIntensity);
    } else {
      analogWrite(_pin2, 0);
    }

    if(_lowerTriggered == true) {
      analogWrite(_pin3, _lowToHighIntensity);
    } else {
      analogWrite(_pin3, 0);
    }

    _lowToHighIntensity += 10;

    if(_lowToHighIntensity >= 260) {
      _lowToHighIntensity = 0;
    }

    _patternTimer = millis();

  }


}


void HapticController::pattern3(FlexSensor *flex, int pin) {

  int flexValue = flex->getValue();
  int upperBound = 35;
  int lowerBound = -35;

  if(flexValue < lowerBound || flexValue > upperBound) {
    analogWrite(pin, 255);
  } else {
    analogWrite(pin, 0);
  }

}

void HapticController::pattern4(int pin) {
  analogWrite(pin, 255);

}
