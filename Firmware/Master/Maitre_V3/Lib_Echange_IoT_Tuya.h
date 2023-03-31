// Librairie de gestion de la communication avec la carte IOT Tuya 

/* 
 *  Connections:
 *  VMA354    Arduino UNO           Arduino MEGA          Arduino Nano Every
 *  VCC       5V                    5V                    5V
 *  GND       GND                   GND                   GND
 *  TX        PIN2  (SWserial RX)   PIN19 (Serial1 RX1)   PIN RX0 (Serial1 RX0)
 *  RX        PIN3  (SWserial TX)   PIN18 (Serial1 TX1)   PIN TX1 (Serial1 TX1)
 */

#include "Tuyav.h"
#include "global.h"
#include "SoftwareSerial.h"

//selection of Serial port
//#if defined(ARDUINO_AVR_UNO)     //Arduino UNO board: use SoftwareSerial with pins you select, see https://www.arduino.cc/en/Reference/softwareSerial
//SoftwareSerial mySWserial(2, 3); //RX,TX (2 and 3 are recommended)
//Tuyav tuyav(&mySWserial);
//#else //Arduino Mega board: User can choose HardwareSerial: Serial1/Serial2/Serial3
//Tuyav tuyav(&Serial1); //Serial1 is pin 18/19 on a Arduino Mega or pin TX1/RX0 on a Arduino Nano Every
//#endif

void IoT_Tuya_Start (){

    Serial.begin(9600);
    
    //define the TUYA pins
    // There are 3 digital inputs, 3 analog inputs, 5 digital output and 3 analog outputs available
    // If you do not use a pin, set the pin as PIN_UNUSED
    
//    tuyav.setDigitalInputs(PIN_UNUSED, PIN_UNUSED, PIN_UNUSED);                  //Set DigitalInputs
//    tuyav.setAnalogInputs(PIN_UNUSED, PIN_UNUSED, PIN_UNUSED);                   //Set AnalogInputs
//    tuyav.setDigitalOutputs(PIN_UNUSED, PIN_UNUSED, PIN_UNUSED, PIN_UNUSED, PIN_UNUSED); //SetDigitalOutputs
//    tuyav.setAnalogOutputs(PIN_UNUSED, PIN_UNUSED, PIN_UNUSED);                  //Set AnalogOutputs (PWM digital pins)

}

void IoT_Tuya_Send (){

//ESSAI

}
