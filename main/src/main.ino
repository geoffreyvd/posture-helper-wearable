
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

//kalibration of the flex sensors, min as in smallest angle
const int STRAIGHT_VALUE = 370;
const int MIN_VALUE = 450;  //utmost value in postive direction
const int MAX_VALUE = 150;  //utmost value in opposite (negative) direction

int flexValue1 = 0;
int flexValue2 = 0;
int flexValue3 = 0;

//initialize new FlexSensors
FlexSensor flex1(A0, STRAIGHT_VALUE, MIN_VALUE, MAX_VALUE);
FlexSensor flex2(A1, STRAIGHT_VALUE, MIN_VALUE, MAX_VALUE);
FlexSensor flex3(A2, STRAIGHT_VALUE, MIN_VALUE, MAX_VALUE);
HapticController haptic1(hapticfeedbackPins, 1);
/**
 * [setup description]
 */
void setup() {
        //Sets the data rate in bits per second
        Serial.begin(9600);
}

/**
 * [loop description]
 */
void loop() {
        //Read the value of the FlexSensor
        flexValue1 = flex1.getValue();
        flexValue2 = flex2.getValue();
        flexValue3 = flex3.getValue();

        //pass flex values to haptic controller, to actiavte a pattern
        haptic1.update(flexValue1, flexValue2, flexValue3);

        // debugging, DONT FORGET TO UNCOMMENT SERIAL.BEGIN IN SETUP
        Serial.println("----flex values---");
        Serial.println(flexValue1);
        Serial.println(flexValue2);
        Serial.println(flexValue3);
        delay(500);
}
