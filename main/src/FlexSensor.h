/*
 * FlexSensor.h - Library for using flex sensors
 * Created by Geoffrey van Driessel, November 11, 2017.
 */
#ifndef FlexSensor_h
#define FlexSensor_h


class FlexSensor
{
public:
FlexSensor(int pin, float straightResistance, float maximumResistance);
float getResistance(float circuitVoltage, float vdcDividerResistance);
float readVoltage(float circuitVoltage);
private:

/**
 * The used Pin
 */
int _pin;
/**
 *  The resistance of the FlexSensor when it's straight (unbended)
 *
 */
float _straightResistance;

/**
 *  The resistance of the FlexSensor at 90 deg
 */
float _maximumResistance;

/**
 * This holds current resistance when the FlexSensor bends
 */
float _currentResistance;

};

#endif
