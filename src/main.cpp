#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SerialUtils.h>

#define SERIAL_BAUD_RATE 9600
#define RDM6300_TX_PIN 10
#define RDM6300_RX_PIN 11

SoftwareSerial rdm6300Serial(RDM6300_TX_PIN, RDM6300_RX_PIN);

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);

    pinMode(RDM6300_TX_PIN, INPUT);
    pinMode(RDM6300_RX_PIN, OUTPUT);
    rdm6300Serial.begin(SERIAL_BAUD_RATE);
}

byte data[12];

void loop() {

    //SerialUtils::readBytesPortion(rdm6300Serial, 54, 66, data);
    SerialUtils::readBytesPortion(rdm6300Serial, 2, 3, data);

    //print data

    for (int i = 0; i < 12; i++) {
        Serial.println(data[i]);
    }

    Serial.println("------");

    /* if (rdm6300Serial.available()) {

         //Discard until the start character to avoid wrong reading
         while (rdm6300Serial.peek() == 3 || rdm6300Serial.peek() != 2) {
             Serial.println("Discard!");
             rdm6300Serial.read();
         }

         while (rdm6300Serial.peek() == 2 || rdm6300Serial.peek() != 3) {
             int byte = rdm6300Serial.read();
             Serial.println(byte);
         }
     }*/

    /* if (rdm6300Serial.available() > 0 && rdm6300Serial.peek() == 2) {
         int byte = rdm6300Serial.read();

         if (byte == 3) {

         }

         Serial.println(byte);
     } else {
         //Discard

         while (rdm6300Serial.available() > 0 )
     }*/

}
