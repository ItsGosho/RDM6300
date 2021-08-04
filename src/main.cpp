#include <Arduino.h>
#include <SoftwareSerial.h>
#include "SerialUtils.h"
#include "GenericUtils.h"

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

void loop() {

    //SerialUtils::readBytesPortion(rdm6300Serial, 54, 66, data);
    byte rdm6300Bytes[12];
    SerialUtils::readBytesPortion(rdm6300Serial, 2, 3, rdm6300Bytes);

    char asciiData[8];
    for (int i = 2; i < 10; ++i) {
        asciiData[i - 2] = rdm6300Bytes[i];
    }


    Serial.println(GenericUtils::convertHexToDecimal(asciiData));

}
