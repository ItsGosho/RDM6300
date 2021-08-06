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

bool RDM6300::isChecksumValid(const byte (& rdm6300Bytes)[12]) {

    unsigned long checksumData = 0;
    for (int i = DATA_START_INDEX; i <= DATA_END_INDEX; i += 2) {
        byte forConversion[2] = {rdm6300Bytes[i], rdm6300Bytes[i + 1]};

        checksumData ^= GenericUtils::convertHexToDecimalRanged(forConversion, 0, 1);
    }

    unsigned long checksumReceived = GenericUtils::convertHexToDecimalRanged(rdm6300Bytes, 10, 11);

    return checksumData == checksumReceived;
}
