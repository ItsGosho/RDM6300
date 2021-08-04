#include "GenericUtils.h"

unsigned long GenericUtils::pow(const int& number, const int& exponent) {

    unsigned long result = 1;

    for (int i = 0; i < exponent; ++i)
        result *= number;

    return result;
}

unsigned long GenericUtils::convertHexToDecimal(const char& character) {

    unsigned long value = (int) character - 48;

    if (value < 10)
        return value;

    if (character == 'A')
        return 10;

    if (character == 'B')
        return 11;

    if (character == 'C')
        return 12;

    if (character == 'D')
        return 13;

    if (character == 'E')
        return 14;

    if (character == 'F')
        return 15;

    return value;
}