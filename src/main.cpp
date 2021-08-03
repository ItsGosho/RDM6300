#include <Arduino.h>
#include <SoftwareSerial.h>

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

    if (rdm6300Serial.available()) {
        Serial.println("Available");
    }

}
