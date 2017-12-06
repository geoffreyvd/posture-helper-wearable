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
    }
}

/**
 * [HapticController::pattern1 Use PWM to adjust the intensity of haptic vibration based on the angle of the flex sensor]
 */
void HapticController::pattern1(FlexSensor flex, int pin, int amplifier){
        int intensity = flex.getValue();
        //Serial.println("intensity: " + String(pin) +  " " + String(intensity));

        //assume that value is given between -180 and +80, make negative postive so it can be used to map intensity
        if(intensity < 0){
          intensity = 0 - intensity;
        }

        intensity = (intensity * amplifier) / 100;

        intensity = constrain(map(intensity, 0, flex._minimumValueCalibrated, 0, 255), 0, 255);

        analogWrite(pin, intensity);
}
