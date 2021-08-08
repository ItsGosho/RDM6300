#include "GenericUtils.h"

/**
 * @param base The base
 * @param exponent The exponent for the base
 * @return The given base raised to the given exponent.
 */
unsigned long GenericUtils::pow(const int& base, const int& exponent) {

    unsigned long result = 1;

    for (int i = 0; i < exponent; ++i)
        result *= base;

    return result;
}

/**
 * Will convert a character representation of HEX to its decimal form.
 *
 * Example:
 *
 * ASCI DECIMAL
 * '2' -> 2
 * '9' -> 9
 * 'A' -> 10
 * 'E' -> 14
 *
 * @param hex The character to be converted to HEX
 * @return The converted character
 */
unsigned long GenericUtils::convertHexToDecimal(const char& hex) {

    unsigned long value = (int) hex - 48;

    if (value < 10)
        return value;

    if (hex == 'A')
        return 10;

    if (hex == 'B')
        return 11;

    if (hex == 'C')
        return 12;

    if (hex == 'D')
        return 13;

    if (hex == 'E')
        return 14;

    if (hex == 'F')
        return 15;

    return value;
}