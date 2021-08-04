#ifndef RDM6300_SERIALUTILS_H
#define RDM6300_SERIALUTILS_H

#include <SoftwareSerial.h>

typedef unsigned char byte;

namespace SerialUtils {

    template<size_t S>
    void readBytesUntil(SoftwareSerial& softwareSerial, const byte& from, const byte& to, byte (& into)[S]) {

        /*TODO: If data index gets bigger than the S then something like error IDK :D*/

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
                    continue;
                }

                if (softwareSerial.peek() != from && frameStarted && softwareSerial.peek() != to) {
                    into[dataIndex] = softwareSerial.read();
                    dataIndex++;
                    continue;
                }

                if (softwareSerial.peek() == to && frameStarted) {
                    /*    frameStarted = false;
                        dataIndex = 0;*/
                    //TODO: return data
                    successfulRead = true;
                    softwareSerial.read();
                    break;
                }

                //Discard byte
                softwareSerial.read();
            }
        }
    }
}

#endif //RDM6300_SERIALUTILS_H
