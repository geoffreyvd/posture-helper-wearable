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
HapticController::HapticController(int pinArray[])
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
        _previousMillis = millis();
}

/**
 *
 * @param flex1 Amount of resistance for 1st FlexSensor
 * @param flex2 Amount of resistance for 2nd FlexSensor
 * @param flex3 Amount of resistance for 3rd FlexSensor
 */
void HapticController::monitorAndUpdate(float flex1, float flex2, float flex3)
{
        int pattern1Threshhold = 55;
        if(flex1 > pattern1Threshhold) {
                pattern1(_pin1, _pin2);
        }
        else{
                turnOff(_pin1, _pin2);
        }
        if(flex2 > pattern1Threshhold) {
                pattern1(_pin3, _pin4);
        }
        else{
                turnOff(_pin3, _pin4);
        }
        if(flex3 > pattern1Threshhold) {
                pattern1(_pin5, _pin6);
        }
        else{
                turnOff(_pin5, _pin6);
        }
}

/**
 * [HapticController::pattern1 Turns on given feedback motors]
 * @param  pin1 A pin of feedback motor
 * @param  pin2 A pin of feedback motor
 */
void HapticController::pattern1(int pin1, int pin2){
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, HIGH);
}

/**
 * [HapticController::turnOff Turns off given feedback motors]
 * @param  pin1 A pin of feedback motor
 * @param  pin2 A pin of feedback motor
 */
void HapticController::turnOff(int pin1, int pin2){
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
}
