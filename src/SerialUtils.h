#ifndef RDM6300_SERIALUTILS_H
#define RDM6300_SERIALUTILS_H

#include <Stream.h>

typedef unsigned char byte;

namespace SerialUtils {

    template<size_t S>
    void readBytesPortion(Stream& serial, const byte& from, const byte& to, byte (& into)[S]) {

        size_t dataIndex = 0;
        bool frameStarted = false;

        while (true) {

            while (serial.available()) {

                if (serial.peek() == from && !frameStarted) {
                    frameStarted = true;
                    serial.read();
                    continue;
                }

                if (serial.peek() == from && frameStarted) {
                    frameStarted = false;
                    dataIndex = 0;
                    continue;
                }

                if (serial.peek() != from && frameStarted && serial.peek() != to) {
                    into[dataIndex] = serial.read();
                    dataIndex++;
                    continue;
                }

                if (serial.peek() == to && frameStarted) {
                    serial.read();
                    return;
                }

                serial.read();
            }
        }
    }
}

#endif //RDM6300_SERIALUTILS_H