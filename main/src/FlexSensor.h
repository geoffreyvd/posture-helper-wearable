/*
 * FlexSensor.h - Library for using flex sensors
 * Created by Geoffrey van Driessel, November 11, 2017.
 */
#ifndef FlexSensor_h
#define FlexSensor_h


class FlexSensor
{
public:
  FlexSensor();
  FlexSensor(int pin, int straightValue, int minimumValue, int maximumValue);
  int getValue();
  int _minimumValueAnalog;
  int _maximumValueAnalog;
  int _minimumValueCalibrated;
  int _maximumValueCalibrated;
  int _straightValue;
private:
  int _pin;


};

#endif
