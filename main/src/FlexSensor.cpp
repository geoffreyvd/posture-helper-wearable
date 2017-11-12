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
FlexSensor::FlexSensor(int pin, float straightResistance,
                       float maximumResistance)
{
        pinMode(pin, INPUT);
        _pin = pin;
        _straightResistance = straightResistance;
        _maximumResistance = maximumResistance;
}

/**
 * [FlexSensor::readVoltage reads the voltage of the assigned PIN ]
 * @return the voltage as an integer between 0 and 1024
 */
float FlexSensor::readVoltage(float circuitVoltage)
{
        int inputVoltageDigital = analogRead(_pin);
        return (inputVoltageDigital * circuitVoltage) / 1023.0;
}

/**
 * [FlexSensor::getResistance this function calculates the resistance based on
 * the readin voltage from a specific Analog input pin ]
 * @param  circuitVoltage       In volt. The output voltage the Arduino gives
 * @param  vdcDividerResistance  In Ohm. The amount Ohms of the resistor that is
 * connected to the FlexSensor
 * @return                      in Ohm. The amount of resistance.
 */
float FlexSensor::getResistance(float circuitVoltage, float vdcDividerResistance)
{
        float flexADC = readVoltage(circuitVoltage);
        return vdcDividerResistance * (circuitVoltage/ flexADC - 1.0);
}
