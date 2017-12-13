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
}

// return a value between (minimum value and maximum value) - straightValue. example range : -180 till +80 positive bent
int FlexSensor::getValue()
{
  return (analogRead(_pin) - _straightValue);
}

void FlexSensor::updateCalibratedValues(int val) {
  _minimumValueCalibrated = _minimumValueAnalog - val;
  _maximumValueCalibrated = _maximumValueAnalog - val;
}
