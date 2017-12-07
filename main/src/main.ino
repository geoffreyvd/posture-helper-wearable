
#include "FlexSensor.h"
#include "HapticController.h"
#include "Arduino.h"

/**
 * This array represents range of DigitalPins which will be set to HIGH when
 * the FlexSensor passes a predefined threshold.
 * Each Pin will will form a power source for HapticFeedback motors
 *
 */
const int hapticfeedbackPins[6] = {3, 5, 6};
const int selectedPattern = 1;

//kalibration of the flex sensors, min as in smallest angle
const int STRAIGHT_VALUE_TOP = 290;
const int STRAIGHT_VALUE_MIDDLE = 385;
const int STRAIGHT_VALUE_BOTTOM = 325;
const int MIN_VALUE_TOP = 420;  //utmost value in postive direction
const int MAX_VALUE_TOP = 100;  //utmost value in opposite (negative) direction
const int MIN_VALUE_MIDDLE = 500;
const int MAX_VALUE_MIDDLE = 230;
const int MIN_VALUE_BOTTOM = 450;
const int MAX_VALUE_BOTTOM = 230;


unsigned long timeSinceCommunication = 0;
unsigned long timeCurrent = 0;
const unsigned long communicationDelay = 500; // 500ms

int flexValue1;
int flexValue2;
int flexValue3;

//buffer for sending timestamp(long) to serial
byte buffer[11];
byte endingByte = 255;
//initialize new FlexSensors
FlexSensor flex1(A0, STRAIGHT_VALUE_TOP, MIN_VALUE_TOP, MAX_VALUE_TOP);
FlexSensor flex2(A1, STRAIGHT_VALUE_MIDDLE, MIN_VALUE_MIDDLE, MAX_VALUE_MIDDLE);
FlexSensor flex3(A2, STRAIGHT_VALUE_BOTTOM, MIN_VALUE_BOTTOM, MAX_VALUE_BOTTOM);
HapticController haptic1(hapticfeedbackPins, selectedPattern, flex1, flex2, flex3);
/**
 * [setup description]
 */
void setup() {
        //Sets the data rate in bits per second
        Serial.begin(9600);
        //MessageType1 (start, after calibration) - calibrationFlexValue1 - calibrationFlexValue2 - calibrationFlexValue3 - pattern - endingByte
        //Serial.write(selectedPattern, endingByte);
        //TODO calibration each flexsensor, pass those values to flex objects and haptic controller,
        //and then calibrate user flex values and write in starting message
        Serial.print(String(flex1.getValue()) + ",");
        Serial.print(String(flex2.getValue()) + ",");
        Serial.print(String(flex3.getValue()) + ",");
        Serial.print(String(selectedPattern));
        Serial.println();
}

/**
 * [loop description]
 */
void loop() {
        timeCurrent = millis();

        //pass flex values to haptic controller, to activate a pattern
        haptic1.update();
        flexValue1 = flex1.getValue();
        flexValue2 = flex2.getValue();
        flexValue3 = flex3.getValue();

        if(timeCurrent > timeSinceCommunication + communicationDelay){
                // buffer[0] = timeCurrent & 255;
                // buffer[1] = (timeCurrent >> 8) & 255;
                // buffer[2] = (timeCurrent >> 16) & 255;
                // buffer[3] = (timeCurrent >> 24) & 255;
                // buffer[4] = flexValue1 & 255;
                // buffer[5] = (flexValue1 >> 8) & 255;
                // buffer[6] = flexValue2 & 255;
                // buffer[7] = (flexValue2 >> 8) & 255;
                // buffer[8] = flexValue3 & 255;
                // buffer[9] = (flexValue3 >> 8) & 255;
                // buffer[10] = endingByte;




                //MessageType2 (every cycle)  - Total millis since start - FlexSensorValue1 - FlexSensorValue2 - FlexSensorValue3 - endingByte
                //Serial.write(buffer + "," + flexValue1 + "," + flexValue2 + "," + flexValue3 + endingByte);
                //flex values will alsohave to be buffered...

                Serial.print(String(timeCurrent) + ",");
                Serial.print(String(flexValue1) + ",");
                Serial.print(String(flexValue2) + ",");
                Serial.print(String(flexValue3));
                Serial.println();



                timeSinceCommunication = millis();
        }
}
