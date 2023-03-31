
/***** Controleur de puissance *******/

#include <Wire.h>
#include <string.h>
#include <Streaming.h>

#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 11); // RX, TX//on informe le microcontrôleur que l'on utilise ses broches pour une connexion série
String readString;

// the pin on which the zero signal is received
#define PIN_ZERO 2

// the pin on which the SCR signal is emitted
#define PIN_SCR 4

// Définition des adresses logiques des esclaves I2C.
#define I2C_SLAVE_SCR 9

// the current power value, in percent of time
int ConsVarECS = 10;

// armed in the ISR to indicate the zero crossing
volatile bool triggered = false;


// ISR called on zero crossing
void onZero() {
    triggered = true;
}

void setup() {

    /* Initialise serial link */
Serial.begin(115200);
mySerial.begin(115200);

    attachInterrupt(digitalPinToInterrupt(PIN_ZERO), onZero, CHANGE);

    pinMode(PIN_SCR, OUTPUT);
    digitalWrite(PIN_SCR, LOW);

Wire.begin(I2C_SLAVE_SCR);
Wire.onReceive (receiveEvent);
int ConsVarECS = Wire.read();
Serial.println(ConsVarECS);

}

void loop() {


   
 

Wire.begin(I2C_SLAVE_SCR);
Wire.onReceive (receiveEvent);

   for (int t=0; t<500; t++)
   {
    if(triggered) {
        triggered = false;
        if(ConsVarECS > 0) {
            // power=100%: no wait, power=0%: wait 10ms
            int delay = ConsVarECS==100? 30 : (100-ConsVarECS)*100;
            delayMicroseconds(delay);

            // generate a pulse (below 50% this is a short pulse, above the pulse has a 3ms duration)
            digitalWrite(PIN_SCR, HIGH);
            delayMicroseconds(ConsVarECS < 50 ? 5 : 3000);
            digitalWrite(PIN_SCR, LOW);

        }
    }
  }
 Serial << F("power =") << ConsVarECS << endl;
}

void receiveEvent() { 
  ConsVarECS = Wire.read ();
  Serial.println (ConsVarECS);
}
