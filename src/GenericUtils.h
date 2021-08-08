#ifndef RDM6300_GENERICUTILS_H
#define RDM6300_GENERICUTILS_H

#include <Arduino.h>

namespace GenericUtils {

    unsigned long pow(const int& base, const int& exponent);

    unsigned long convertHexToDecimal(const char& hex);

    /**
     * Will convert a given HEX to decimal.
     *
     * Example:
     *
     * {'5', '6', 'A', '1', 'F'} or 56A1F
     *
     * That is (5 × 16⁴) + (6 × 16³) + (10 × 16²) + (1 × 16¹) + (15 × 16⁰) = (354847)₁₀
     *
     * @param hex The hex symbols, which will be converted. They are treated as one hex number
     * @param startIndex The start index of the sequence - inclusive
     * @param endIndex  The end index of the sequence - inclusive
     * @return The converted hex to decimal
     */
    template<size_t S>
    unsigned long convertHexToDecimalRanged(const byte (& hex)[S], const size_t& startIndex, const size_t& endIndex) {

        size_t exponent = 0;
        unsigned long result = 0;

        for (size_t i = endIndex; i >= startIndex && i <= endIndex; i--) {
            result += convertHexToDecimal(hex[i]) * pow(16, exponent);
            exponent++;
        }

        return result;
    }

    /**
     * Will concat a given sequence and return it as integer.
     * It only works with positive numbers.
     *
     * Example:
     *
     * {'5', '3', '2'}
     *
     * That is 5 x 100 + 3 x 10 + 2 x 1 = 532 as integer
     *
     * @param characters The characters representing a integer
     * @param startIndex The start index of the sequence - inclusive
     * @param endIndex  The end index of the sequence - inclusive
     * @return The concatenated sequence
     */
    template<size_t S>
    unsigned long concatCharactersRanged(const byte (& characters)[S], const size_t& startIndex, const size_t& endIndex) {

        unsigned long multiplier = 1;
        unsigned long result = 0;

        for (size_t i = endIndex; i >= startIndex && i <= endIndex; i--) {
            result += (characters[i] - '0') * multiplier;
            multiplier *= 10;
        }

        return result;
    }
}

#endif //RDM6300_GENERICUTILS_H
