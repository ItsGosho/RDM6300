#ifndef RDM6300_SERIALUTILS_H
#define RDM6300_SERIALUTILS_H

#include <Stream.h>

typedef unsigned char byte;

namespace SerialUtils {

    template<size_t S>
    void readBytesPortion(Stream& serial, const byte& startByte, const byte& endByte, byte (& into)[S]) {

        size_t dataIndex = 0;
        bool frameStarted = false;

        while (true) {

            while (serial.available()) {

                byte currentByte = serial.peek();

                if (currentByte == startByte && !frameStarted) {
                    frameStarted = true;
                    serial.read();
                    continue;
                }

                if (currentByte == startByte && frameStarted) {
                    frameStarted = false;
                    dataIndex = 0;
                    continue;
                }

                if (currentByte != startByte && frameStarted && currentByte != endByte) {
                    into[dataIndex] = serial.read();
                    dataIndex++;
                    continue;
                }

                if (currentByte == endByte && frameStarted) {
                    serial.read();
                    return;
                }

                serial.read();
            }
        }
    }
}

#endif //RDM6300_SERIALUTILS_H
