#include "FlexSensor.h"
#include "HapticController.h"
//
// FlexSensor flex1(13);
// HapticController hapticController(1,2,3,4,5,6);
//
// void setup() {
//   // put your setup code here, to run once:
// }
//
// void loop() {
//   // put your main code here, to run repeatedly:
//   flex1.read();
//   hapticController.update(101,1,101);
// }


/**
 * Pins which are connected to voltage divider output
 * There are three pins. Each pin corresponds to one FlexSensor
 *
 *
 * @todo Replace the current structure with an array
 */
const int FLEX_PIN = A0;
const int FLEX_PIN1=A1;
const int FLEX_PIN2=A2;

/**
 * This array represents range of DigitalPins which will be set to HIGH when
 * the FlexSensor passes a predefined threshold.
 * Each Pin will will form a power source for HapticFeedback motors
 *
 */
int hapticfeedbackPins[3] = {11,12,13};



/**
 * Measured voltage of Ardunio 5V line
 * This value wouldn't be changed. This is the amount of Volt the Arduino gives
 */
const float OUTPUT_VOLTAGE= 4.85;

/**
 * Theoratically it's 47k resistor
 *
 */
const float vdcDividerResistance = 46500.0;

/**
 *  The resistance of the FlexSensor when it's straight (unbended)
 *
 */
const float STRAIGHT_RESISTANCE = 30000.0;

/**
 *  The resistance of the FlexSensor at 90 deg
 */
const float BEND_RESISTANCE = 60000.0;
/**
 * [setup description]
 */
void setup() {
    //Sets the data rate in bits per second
    Serial.begin(9600);
    /**
     * Setting up the mode of each PIN
     */
    pinMode(FLEX_PIN, INPUT);
    pinMode(hapticfeedbackPins[1],OUTPUT);
    digitalWrite(hapticfeedbackPins[1], HIGH);
}


/**
 * [loop description]
 */
void loop() {

  /**
   * The following chunck of code should be repeated for each FlexSensor we have
   *
   */
  // Read the ADC, and calculate voltage and resistance from it
 int flexADC = analogRead(FLEX_PIN);

 //The input voltage coming through the FlexSensor
 float flexSensorOuputVoltage = flexADC * OUTPUT_VOLTAGE / 1023.0;

 //The input Resistance from the FlexSensor
 float flexSensorOuputResistance = vdcDividerResistance * (OUTPUT_VOLTAGE / flexSensorOuputVoltage - 1.0);
 //Printing values
 Serial.println("Input from the serial port: " + String(flexSensorOuputVoltage) + "Volts" );
 Serial.println("Resistance: " + String(flexSensorOuputResistance/100) + " Kohm");

 /**
  * The code part which be responsible for triggering the HapticFeedback
  * The 55 is an imaginary value. The Threshold should be specified based on
  * research.
  * For now this only turns on a LED
  */
 if((flexSensorOuputResistance/1000) > 55 ){
     digitalWrite(hapticfeedbackPins[1], HIGH);
 }
 else{
    digitalWrite(hapticfeedbackPins[1], LOW);
 }
 Serial.println();
 //delay(1000);

   /**
    * In case of reading a second FlexSensor the could should be put here the same
    * as written above. In case we don't use classes
    *
    */


}
