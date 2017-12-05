/*
 * HapticController.h - Library for controlling haptic units
 * Created by Geoffrey van Driessel, November 11, 2017.
 */
#include "Arduino.h"
#include "HapticController.h"

/**
 * [HapticController::HapticController description]
 * @param pin1 [description]
 * @param pin2 [description]
 * @param pin3 [description]
 * @param pin4 [description]
 * @param pin5 [description]
 * @param pin6 [description]
 */
HapticController::HapticController(int pinArray[], int pattern)
{
        for (int i=0; i<6; i++) {
                pinMode(pinArray[i], OUTPUT);
        }
        _pin1 = pinArray[0];
        _pin2 = pinArray[1];
        _pin3 = pinArray[2];
        _pin4 = pinArray[3];
        _pin5 = pinArray[4];
        _pin6 = pinArray[5];
        _selectedPattern = pattern;
}

/**
 *
 * @param flex1 Amount of resistance for 1st FlexSensor
 * @param flex2 Amount of resistance for 2nd FlexSensor
 * @param flex3 Amount of resistance for 3rd FlexSensor
 */
void HapticController::update(float flex1, float flex2, float flex3)
{
    if (_selectedPattern == 1)
    {        
        pattern1(flex1, _pin1, _pin2);
        pattern1(flex2, _pin3, _pin4);
        pattern1(flex3, _pin5, _pin6);
    }
}

/**
 * [HapticController::pattern1 Use PWM to adjust the intensity of haptic vibration based on the angle of the flex sensor]
 */
void HapticController::pattern1(float flex, int pin1, int pin2){
        int intensity = 0;

        //assume that value is given between -180 and +80, make negative postive so it can be used to map intensity
        if(flex < 0){
          flex = 0 - flex;
        }

        intensity = map(flex, 0, 180, 0, 255);

        analogWrite(pin1, intensity);
        analogWrite(pin2, intensity);
}
