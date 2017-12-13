/*
 * FlexSensor.h - Library for using flex sensors
 * Created by Geoffrey van Driessel, November 11, 2017.
 */
#include "Arduino.h"
#include "FlexSensor.h"

/**
 * [FlexSensor::FlexSensor description]
 * @param pin                [description]
 * @param straightResistance [description]
 * @param maximumResistor    [description]
 */
FlexSensor::FlexSensor(){

}

FlexSensor::FlexSensor(int pin, int straightValue,
                       int minimumValue, int maximumValue)
{
        pinMode(pin, INPUT);
        _pin = pin;
        _straightValue = straightValue;
        _minimumValueAnalog = minimumValue;
        _maximumValueAnalog = maximumValue;
        _minimumValueCalibrated = minimumValue - straightValue;
        _maximumValueCalibrated = maximumValue - straightValue;
        _userCalibrated = straightValue;
        _currentReading = 0;
}

void FlexSensor::read() {
  _currentReading = (analogRead(_pin) - _userCalibrated);
}

// return a value between (minimum value and maximum value) - straightValue. example range : -180 till +80 positive bent
int FlexSensor::getValue()
{
  return _currentReading;
}

void FlexSensor::updateCalibratedValues(int userStraightValue) {
  _userCalibrated = userStraightValue;
  _minimumValueCalibrated = _minimumValueAnalog - userStraightValue + _userCalibrated;
  _maximumValueCalibrated = _maximumValueAnalog - userStraightValue + _userCalibrated;
}
