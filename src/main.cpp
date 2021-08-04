#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SerialUtils.h>

#define SERIAL_BAUD_RATE 9600
#define RDM6300_TX_PIN 10
#define RDM6300_RX_PIN 11

SoftwareSerial rdm6300Serial(RDM6300_TX_PIN, RDM6300_RX_PIN);

unsigned long pow(const int& number, const int& exponent) {

    unsigned long result = 1;

    for (int i = 0; i < exponent; ++i)
        result *= number;

    return result;
}

unsigned long convertHexToDecimal(const char& character) {

    unsigned long value = (int) character - 48;

    if (value < 10)
        return value;

    if (character == 'A')
        return 10;

    if (character == 'B')
        return 11;

    if (character == 'C')
        return 12;

    if (character == 'D')
        return 13;

    if (character == 'E')
        return 14;

    if (character == 'F')
        return 15;

    return value;
}

template<size_t S>
unsigned long convertHexToDecimal(char (& hex)[S]) {

    size_t exponent = 0;
    unsigned long result = 0;

    for (int i = S - 1; i >= 0; i--) {
        result += convertHexToDecimal(hex[i]) * pow(16, exponent);
        exponent++;
    }

    return result;
}

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


    Serial.println(convertHexToDecimal(asciiData));

}
