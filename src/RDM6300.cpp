#include "RDM6300.h"


RDM6300::RDM6300(const short& txPin, const short& rxPin) : txPin(txPin), rxPin(rxPin), serial(txPin, rxPin) {
    pinMode(this->txPin, INPUT);
    pinMode(this->rxPin, OUTPUT);
    this->serial.begin(SERIAL_BAUD_RATE);
}

RFIDTag RDM6300::readTag() {

    byte rdm6300Bytes[12];
    SerialUtils::readBytesPortion(this->serial, START_BYTE, END_BYTE, rdm6300Bytes);

    unsigned long version = GenericUtils::concatCharactersRanged(rdm6300Bytes, DATA_VERSION_START_INDEX,DATA_VERSION_END_INDEX);
    unsigned long id = GenericUtils::convertHexToDecimalRanged(rdm6300Bytes, DATA_TAG_START_INDEX, DATA_TAG_END_INDEX);
    bool isChecksumValid = this->isChecksumValid(rdm6300Bytes);

    return RFIDTag{id, version, isChecksumValid};
}

/**
 * Will compare the calculated checksum from us based on the data with the received one from the device for comparison
 * @param rdm6300Bytes The all received bytes from the device
 * @return If the calculated checksum matched with the received one
 */
bool RDM6300::isChecksumValid(const byte (& rdm6300Bytes)[12]) {

    unsigned long calculatedChecksum = this->calculateChecksum(rdm6300Bytes);
    unsigned long checksumReceived = GenericUtils::convertHexToDecimalRanged(rdm6300Bytes, CHECKSUM_START_INDEX,CHECKSUM_END_INDEX);

    return calculatedChecksum == checksumReceived;
}

/**
 * Each pair of data bytes will be treated as hex, which will be converted to decimal and a XOR operation will be executed on each of them.
 *
 * Provided RDM6300 bytes:
 * [48, 57, 48, 48, 50, 54, 56, 54, 49, 50, 66, 66]
 *
 * The data will be the first 10 bytes:
 * [48, 57, 48, 48, 50, 54, 56, 54, 49, 50]
 *
 * Treat each pair as HEX and XOR it with the rest:
 *
 * [48, 57, 48, 48, 50, 54, 56, 54, 49, 50]
 *   -----    -----   -----   -----   -----
 *  (09) XOR (00) XOR (26) XOR (86) XOR (12)
 *
 *  That will be the calculated checksum.
 *
 *
 * @param rdm6300Bytes The all received bytes from the RDM6300
 * @return The calculated checksum
 */
unsigned long RDM6300::calculateChecksum(const byte (& rdm6300Bytes)[12]) {

    unsigned long calculatedChecksum = 0;

    for (int i = DATA_START_INDEX; i <= DATA_END_INDEX; i += 2) {
        byte forConversion[2] = {rdm6300Bytes[i], rdm6300Bytes[i + 1]};

        calculatedChecksum ^= GenericUtils::convertHexToDecimalRanged(forConversion, 0, 1);
    }

    return calculatedChecksum;
}
