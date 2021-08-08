#ifndef RDM6300_SERIALUTILS_H
#define RDM6300_SERIALUTILS_H

#include <Stream.h>

typedef unsigned char byte;

namespace SerialUtils {


    /**
     * Will read a specific portion of the bytes that have been received on the serial.
     * Let's for example say that, when calling the function the following bytes have been received in the buffer:
     *
     * 10 2 2 45 31 21 32 3 12 13 4 50 2 16 17 3 19
     *      -             -            -       -
     *
     * Then if we specify 2 and 3 as start and end byte we will get the following result in the array that we have provided:
     *
     * 45 31 21 32
     *
     * - When searching for a sequence and a two start bytes are found, but not yet a end byte, then the last found start byte will be counted. That
     *   is clearly visible in the example above.
     *
     * - The other bytes will not be read and will be available for the next function calling eg: they will not be discarded
     *
     * @param serial The serial from which the bytes will be read
     * @param startByte The start byte of the sequence
     * @param endByte The end byte of the sequence
     * @param into The array, which will be filled with the read data
     */
    template<size_t S>
    void readBytesPortion(Stream& serial, const byte& startByte, const byte& endByte, byte (& into)[S]) {

        size_t dataIndex = 0;
        bool frameStarted = false;

        while (true) {

            bool isSuccessfulRead = readAvailablePortionBytes(serial, startByte, endByte, into, frameStarted, dataIndex);

            if (isSuccessfulRead)
                break;
        }
    }

    /**
     * Same as reading a bytes portion, but with timeout.
     *
     * @param readTimeoutMS The max time for finding the sequence
     * @return If the read has timed out.
     */
    template<size_t S>
    bool readBytesPortion(Stream& serial, const byte& startByte, const byte& endByte, byte (& into)[S], const unsigned long& readTimeoutMS) {

        size_t dataIndex = 0;
        bool frameStarted = false;

        unsigned long readStartTimeMS = millis();

        while (true) {

            bool isPortionCompleted = readAvailablePortionBytes(serial, startByte, endByte, into, frameStarted, dataIndex);

            if (isPortionCompleted)
                return false;

            unsigned long totalReadTimeMS = millis() - readStartTimeMS;

            if (totalReadTimeMS >= readTimeoutMS)
                return true;
        }
    }

    template<size_t S>
    bool readAvailablePortionBytes(Stream& serial, const byte& startByte, const byte& endByte, byte (& into)[S], bool& frameStarted, size_t& dataIndex) {

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
                return true;
            }

            serial.read();
        }

        return false;
    }
}

#endif //RDM6300_SERIALUTILS_H
