#ifndef RDM6300_SERIALUTILS_H
#define RDM6300_SERIALUTILS_H

#include <SoftwareSerial.h>

typedef unsigned char byte;

namespace SerialUtils {

    template<size_t S>
    void readBytesUntil(SoftwareSerial& softwareSerial, const byte& from, const byte& to, byte (& into)[S]) {

        int dataIndex = 0;
        bool frameStarted = false;
        bool successfulRead = false;

        while (!successfulRead) {

            while (softwareSerial.available()) {

                if (softwareSerial.peek() == from && !frameStarted) {
                    frameStarted = true;
                    softwareSerial.read();
                    continue;
                }

                if (softwareSerial.peek() == from && frameStarted) {
                    frameStarted = false;
                    dataIndex = 0;
                    continue;
                }

                if (softwareSerial.peek() != from && frameStarted && softwareSerial.peek() != to) {
                    into[dataIndex] = softwareSerial.read();
                    dataIndex++;
                    continue;
                }

                if (softwareSerial.peek() == to && frameStarted) {
                    successfulRead = true;
                    softwareSerial.read();
                    break;
                }

                softwareSerial.read();
            }
        }
    }
}

#endif //RDM6300_SERIALUTILS_H
