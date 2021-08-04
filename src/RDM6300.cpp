#include "RDM6300.h"


RDM6300::RDM6300(const short& txPin, const short& rxPin) : txPin(txPin), rxPin(rxPin), serial(txPin, rxPin) {
    pinMode(this->txPin, INPUT);
    pinMode(this->rxPin, OUTPUT);
    this->serial.begin(SERIAL_BAUD_RATE);
}

RFIDTag RDM6300::readTag() {

    byte rdm6300Bytes[12];
    SerialUtils::readBytesPortion(this->serial, START_BYTE, END_BYTE, rdm6300Bytes);

    /*TODO: Vmesto da gi pulnq, prosto da im se vzimat ot - do*/
    char data[10];
    for (int i = 0; i < 10; ++i) {
        data[i] = rdm6300Bytes[i];
    }

    char versionData[2];
    for (int i = 0; i < 2; ++i) {
        versionData[i] = rdm6300Bytes[i];
    }

    char tagId[8];
    for (int i = 2; i < 10; ++i) {
        tagId[i - 2] = rdm6300Bytes[i];
    }

    char checksum[2];
    for (int i = 10; i < 12; ++i) {
        checksum[i - 10] = rdm6300Bytes[i];
    }

    unsigned long version = GenericUtils::concatCharacters(versionData);
    unsigned long id = GenericUtils::convertHexToDecimal(tagId);

    /*TODO Refactor into its own separate func*/
    unsigned long checksumData = 0;
    for (int i = 0; i < 10; i += 2) {
        char forConversion[2] = {data[i], data[i + 1]};

        checksumData ^= GenericUtils::convertHexToDecimal(forConversion);
    }

    unsigned long checksumReceived = GenericUtils::convertHexToDecimal(checksum);
    bool isChecksumValid = checksumData == checksumReceived;

    return RFIDTag{id, version, isChecksumValid};
}
