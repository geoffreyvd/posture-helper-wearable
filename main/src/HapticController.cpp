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
        for (int i=0; i<3; i++) {
                pinMode(pinArray[i], OUTPUT);
        }
        _pin1 = pinArray[0];
        _pin2 = pinArray[1];
        _pin3 = pinArray[2];
        _selectedPattern = pattern;
}

/**
 *
 * @param flex1 Amount of resistance for 1st FlexSensor
 * @param flex2 Amount of resistance for 2nd FlexSensor
 * @param flex3 Amount of resistance for 3rd FlexSensor
 */
void HapticController::update(int flex1, int flex2, int flex3)
{
    if (_selectedPattern == 1)
    {
        pattern1(flex1, _pin1, 100);
        pattern1(flex2, _pin2, 150);
        pattern1(flex3, _pin3, 200);
    }
}

/**
 * [HapticController::pattern1 Use PWM to adjust the intensity of haptic vibration based on the angle of the flex sensor]
 */
void HapticController::pattern1(int flex, int pin1, int amplifier){
        int intensity = 0;

        //assume that value is given between -180 and +80, make negative postive so it can be used to map intensity
        if(flex < 0){
          flex = 0 - flex;
        }

        flex = (flex * amplifier) / 100;

        intensity = constrain(map(flex, 0, 180, 0, 255), 0, 255);

        analogWrite(pin1, intensity);
}
