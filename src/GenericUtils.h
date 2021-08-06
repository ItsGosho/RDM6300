#ifndef RDM6300_GENERICUTILS_H
#define RDM6300_GENERICUTILS_H

#include <Arduino.h>

namespace GenericUtils {

    unsigned long pow(const int& number, const int& exponent);

    unsigned long convertHexToDecimal(const char& character);

    template<size_t S>
    unsigned long convertHexToDecimal(const char (& hex)[S]) {
        const size_t startIndex = 0;
        const size_t endIndex = S - 1;
        return convertHexToDecimalRanged(hex, startIndex, endIndex);
    }

    template<size_t S>
    unsigned long convertHexToDecimalRanged(const char (& hex)[S], const size_t& startIndex, const size_t& endIndex) {
        size_t exponent = 0;
        unsigned long result = 0;

        for (size_t i = endIndex; i >= startIndex && i <= endIndex; i--) {
            result += convertHexToDecimal(hex[i]) * pow(16, exponent);
            exponent++;
        }

        return result;
    }

    template<size_t S>
    unsigned long concatCharacters(const char (& characters)[S]) {

        unsigned long multiplier = 1;
        unsigned long result = 0;
        for (int i = S - 1; i >= 0; i--) {
            result += (characters[i] - '0') * multiplier;
            multiplier *= 10;
        }

        return result;
    }
}

#endif //RDM6300_GENERICUTILS_H
