
#include "FlexSensor.h"
#include "HapticController.h"
#include "Arduino.h"

/**
 * Measured voltage of Ardunio 5V line
 * This value wouldn't be changed. This is the amount of Volt the Arduino gives
 */
const float circuitVoltage= 4.85;

/**
 * Theoratically it's 47k resistor
 * Each FlexSensor must have its own Resistor
 *
 */
const float vdcDividerResistance = 46500.0;


/**
 * This array represents range of DigitalPins which will be set to HIGH when
 * the FlexSensor passes a predefined threshold.
 * Each Pin will will form a power source for HapticFeedback motors
 *
 */
int hapticfeedbackPins[3] = {11,12,13};

/**
 *  The resistance of the FlexSensor when it's straight (unbended)
 *
 */
const float STRAIGHT_RESISTANCE = 30000.0;

/**
 *  The resistance of the FlexSensor at 90 deg
 */
const float Maximum_RESISTANCE = 60000.0;

//initialize a new FlexSensor
FlexSensor flex1(A0,STRAIGHT_RESISTANCE,Maximum_RESISTANCE);

/**
 * [setup description]
 */
void setup() {
        //Sets the data rate in bits per second
        Serial.begin(9600);
        /**
         * Setting up the mode of each PIN
         */
        pinMode(hapticfeedbackPins[1],OUTPUT);
        digitalWrite(hapticfeedbackPins[1], HIGH);
}

/**
 * [loop description]
 */
void loop() {
        //Read the value of the FlexSensor
        float flexSensorOuputResistance = flex1.getResistance(
          circuitVoltage,vdcDividerResistance);
        //print values for debug & testing  and extra info
        Serial.println("Voltage from the SerialPort "
        + String(flex1.readVoltage(circuitVoltage)) + " Volt" );
        Serial.println(
          "Resistance from the FlexSensor: " +
           String(flexSensorOuputResistance/1000)+ " Kohm");

        /**
         * The code part which be responsible for triggering the HapticFeedback
         * The 55 is an imaginary value. The Threshold should be specified based
         *  on research.
         * For now this only turns on a LED
         */
        if((flexSensorOuputResistance/1000) > 55 ) {
                digitalWrite(hapticfeedbackPins[1], HIGH);
        }
        else{
                digitalWrite(hapticfeedbackPins[1], LOW);
        }
        Serial.println();
        delay(1000);
}
