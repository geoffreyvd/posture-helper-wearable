
#include "FlexSensor.h"
#include "HapticController.h"
#include "Arduino.h"

/**
 * This array represents range of DigitalPins which will be set to HIGH when
 * the FlexSensor passes a predefined threshold.
 * Each Pin will will form a power source for HapticFeedback motors
 *
 */
const int hapticfeedbackPins[6] = {3, 5, 6, 9, 10, 11};
const int selectedPattern = 1

//kalibration of the flex sensors, min as in smallest angle
const int STRAIGHT_VALUE = 370;
const int MIN_VALUE = 450;  //utmost value in postive direction
const int MAX_VALUE = 150;  //utmost value in opposite (negative) direction

int flexValue1 = 0;
int flexValue2 = 0;
int flexValue3 = 0;

unsigned long timeSinceCommunication = 0;
unsigned long timeCurrent = 0;
const unsigned long communicationDelay = 500; // 500ms

//buffer for sending timestamp(long) to serial
byte buffer[4];
byte endingByte = 255;
//initialize new FlexSensors
FlexSensor flex1(A0, STRAIGHT_VALUE, MIN_VALUE, MAX_VALUE);
FlexSensor flex2(A1, STRAIGHT_VALUE, MIN_VALUE, MAX_VALUE);
FlexSensor flex3(A2, STRAIGHT_VALUE, MIN_VALUE, MAX_VALUE);
HapticController haptic1(hapticfeedbackPins, selectedPattern);
/**
 * [setup description]
 */
void setup() {
        //Sets the data rate in bits per second
        Serial.begin(9600);
        //MessageType1 (start, after calibration) - calibrationFlexValue1 - calibrationFlexValue2 - calibrationFlexValue3 - pattern - endingByte
        Serial.write(selectedPattern, endingByte);
        //TODO calibration each flexsensor, pass those values to flex objects and haptic controller, 
        //and then calibrate user flex values and write in starting message
}

/**
 * [loop description]
 */
void loop() {
        timeCurrent = millis();

        //Read the values of the FlexSensor
        flexValue1 = flex1.getValue();
        flexValue2 = flex2.getValue();
        flexValue3 = flex3.getValue();

        //pass flex values to haptic controller, to actiavte a pattern
        haptic1.update(flexValue1, flexValue2, flexValue3);

        if(timeCurrent > timeSinceCommunication + communicationDelay){
                buffer[0] = timeCurrent & 255;
                buffer[1] = (timeCurrent >> 8) & 255;
                buffer[2] = (timeCurrent >> 16) & 255;
                buffer[3] = (timeCurrent >> 24) & 255;
                //MessageType2 (every cycle)  - Total millis since start - FlexSensorValue1 - FlexSensorValue2 - FlexSensorValue3 - endingByte
                Serial.write(buffer + "," + flexValue1 + "," + flexValue2 + "," + flexValue3 + endingByte);
                //flex values will alsohave to be buffered...

                timeSinceCommunication = millis();
        }
}
