#ifndef RDM6300_RDM6300_H
#define RDM6300_RDM6300_H

#include "SerialUtils.h"
#include "GenericUtils.h"
#include <SoftwareSerial.h>

#define START_BYTE 2
#define END_BYTE 3
#define SERIAL_BAUD_RATE 9600

struct RFIDTag {

    unsigned long id;
    unsigned long version;
    bool isChecksumValid;

};

class RDM6300 {

private:
    short txPin;
    short rxPin;
    SoftwareSerial serial;

public:

    RDM6300(const short& txPin, const short& rxPin);

    RFIDTag readTag();

private:

    bool isChecksumValid(const char (& data)[10],const char (&checksum)[2]);
};


#endif //RDM6300_RDM6300_H
