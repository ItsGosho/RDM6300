#ifndef RDM6300_RDM6300_H
#define RDM6300_RDM6300_H

#include "SerialUtils.h"
#include "GenericUtils.h"
#include <SoftwareSerial.h>

#define START_BYTE 2
#define END_BYTE 3
#define SERIAL_BAUD_RATE 9600

#define DATA_VERSION_START_INDEX 0
#define DATA_VERSION_END_INDEX 1
#define DATA_TAG_START_INDEX 2
#define DATA_TAG_END_INDEX 9
#define CHECKSUM_START_INDEX 10
#define CHECKSUM_END_INDEX 11
#define DATA_START_INDEX 0
#define DATA_END_INDEX 9

struct RFIDTag {

    unsigned long id;
    unsigned long version;
    bool isChecksumValid;
    bool isReadTimedOut;

};

class RDM6300 {

private:
    short txPin;
    short rxPin;
    SoftwareSerial serial;

public:

    RDM6300(const short& txPin, const short& rxPin);

    RFIDTag readTag();
    RFIDTag RDM6300::readTag(const unsigned long& readTimeoutMS);

private:

    unsigned long calculateChecksum(const byte (& rdm6300Bytes)[12]);
    bool isChecksumValid(const byte (& rdm6300Bytes)[12]);
    RFIDTag convertReadData(const byte (& rdm6300Bytes)[12],const bool& hasReadTimedOut);
};


#endif //RDM6300_RDM6300_H
