
#include "FlexSensor.h"
#include "HapticController.h"
#include "Arduino.h"

/**
 * This array represents range of DigitalPins which will be set to HIGH when
 * the FlexSensor passes a predefined threshold.
 * Each Pin will will form a power source for HapticFeedback motors
 *
 */
const int hapticfeedbackPins[3] = {3, 5, 6};
const int selectedPattern = 2;

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
const int STATUS_STOPPED = 0;
const int STATUS_CALIBRATE = 1;
const int STATUS_LOGGING = 2;


unsigned long timeSinceCommunication = 0;
unsigned long timeCurrent = 0;
const unsigned long communicationDelay = 100; // 500ms
int currentStatus;

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
HapticController haptic1(hapticfeedbackPins, selectedPattern, &flex1, &flex2, &flex3);
/**
 * [setup description]
 */
void setup() {
        //Sets the data rate in bits per second
        Serial.begin(9600);
        currentStatus = STATUS_STOPPED;
}
/**
 * [loop description]
 */
void loop() {
        timeCurrent = millis();


        //pass flex values to haptic controller, to activate a pattern
        flex1.read();
        flex2.read();
        flex3.read();
        flexValue1 = flex1.getValue();
        flexValue2 = flex2.getValue();
        flexValue3 = flex3.getValue();
        haptic1.update();


        if(Serial.available() > 0) {
          currentStatus = Serial.read();
        }

        if(currentStatus == STATUS_CALIBRATE) {


          flex1.updateCalibratedValues(flexValue1);
          flex2.updateCalibratedValues(flexValue2);
          flex3.updateCalibratedValues(flexValue3);
          Serial.print(flexValue1);
          Serial.print(",");
          Serial.print(flexValue2);
          Serial.print(",");
          Serial.print(flexValue3);
          Serial.print(",");
          Serial.print(selectedPattern);
          Serial.println();
          currentStatus = STATUS_STOPPED;

        } else if(currentStatus == STATUS_LOGGING) {

          if(timeCurrent > timeSinceCommunication + communicationDelay){
            //MessageType2 (every cycle)  - Total millis since start - FlexSensorValue1 - FlexSensorValue2 - FlexSensorValue3 - endingByte

            Serial.print(String(timeCurrent) + ",");
            Serial.print(String(flexValue1) + ",");
            Serial.print(String(flexValue2) + ",");
            Serial.print(String(flexValue3));
            Serial.println();

            timeSinceCommunication = millis();
          }
      }
}
