#include <Arduino.h>
#include <SerialPrintF.h>
#include "RDM6300.h"

#define SERIAL_BAUD_RATE 9600
#define RDM6300_TX_PIN 10
#define RDM6300_RX_PIN 11

RDM6300 rdm6300(RDM6300_TX_PIN, RDM6300_RX_PIN);

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
}

void loop() {

    RFIDTag rfidTag = rdm6300.readTag();

    serial_printf(Serial, "Version: %l, Id: %l, Checksum: %s\n",
                  rfidTag.version,
                  rfidTag.id,
                  rfidTag.isChecksumValid ? "true": "false");
}
