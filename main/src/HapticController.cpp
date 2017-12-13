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
HapticController::HapticController(int pinArray[], int pattern, FlexSensor &flex1, FlexSensor &flex2, FlexSensor &flex3)
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
        _patternPulseDelay = 10;
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
        pattern1(_flex1, _pin1, 200);
        pattern1(_flex2, _pin2, 150);
        pattern1(_flex3, _pin3, 100);
    }else if(_selectedPattern == 2){
        pattern2(_flex1, _pin1);
        pattern2(_flex2, _pin2);
        pattern2(_flex3, _pin3);

    } else if(_selectedPattern == 3){
        pattern3(_flex1, _pin1);
        pattern3(_flex2, _pin2);
        pattern3(_flex3, _pin3);
    } else if(_selectedPattern == 4){
        pattern4(_flex1, _pin1);
        pattern4(_flex2, _pin2);
        pattern4(_flex3, _pin3);

    }
}

/**
 * [HapticController::pattern1 Use PWM to adjust the intensity of haptic vibration based on the angle of the flex sensor]
 */
void HapticController::pattern1(FlexSensor flex, int pin, int amplifier){
        int intensity = flex.getValue();
        //Serial.println("intensity: " + String(pin) +  " " + String(intensity));

        //assume that value is given between -180 and +80, make negative postive so it can be used to map intensity
        if(intensity > 0){
          intensity = intensity * -1;
        }

        intensity = (intensity * amplifier) / 100;

        intensity = constrain(map(intensity, 0, flex._maximumValueCalibrated, 0, 255), 0, 255);

        analogWrite(pin, intensity);
}

void HapticController::pattern2(FlexSensor flex, int pin) {

    unsigned long _currentTime;
    int flexValue = flex.getValue();
    int range = flex._minimumValueCalibrated - flex._maximumValueCalibrated;
    int threshold = (range / 90) * 2; // find analog value for 1 degree and multiply by threshold required (i.e +- 20 degrees)
    int upperBound = flex._userCalibrated - threshold;
    int lowerBound = flex._userCalibrated + (threshold * -1);

    // Serial.println("Lowerbound: " + String(lowerBound));
    // Serial.println("Uppbound: " + String(upperBound));
    // Serial.println("flexValue: " + String(flexValue));

    if(flexValue < lowerBound) {

          _currentTime = millis();

          if(_currentTime > _patternTimer + _patternPulseDelay ) {
            analogWrite(pin, _lowToHighIntensity);
            _lowToHighIntensity += 25;
            _patternTimer = millis();
          }

          if(_lowToHighIntensity >= 255) {
            _lowToHighIntensity = 0;
          }

        } else if(flexValue > upperBound) {

          _currentTime = millis();

          if(_currentTime > _patternTimer + _patternPulseDelay ) {
            analogWrite(pin, _highToLowIntensity);
            _highToLowIntensity -= 25;
            _patternTimer = millis();
          }

          if(_highToLowIntensity <= 0) {
            _highToLowIntensity = 255;
          }

        } else {
          _lowToHighIntensity = 0;
          _highToLowIntensity = 255;
          analogWrite(pin, 0);
        }

}


void HapticController::pattern3(FlexSensor flex, int pin) {

    int flexValue = flex.getValue();
    int range = flex._minimumValueCalibrated - flex._maximumValueCalibrated;
    int threshold = (range / 90) * 20; // find analog value for 1 degree and multiply by threshold required (i.e +- 20 degrees)
    int upperBound = flex._userCalibrated - threshold;
    int lowerBound = flex._userCalibrated + (threshold * -1);

    if(flexValue < lowerBound || flexValue > upperBound) {
      analogWrite(pin, 255);
    } else {
      analogWrite(pin, 0);
    }

}

void HapticController::pattern4(FlexSensor flex, int pin) {
  analogWrite(pin, 255);

}
