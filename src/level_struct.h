#ifndef LEVEL_STRUCT_H
#define LEVEL_STRUCT_H
#include "bn_log.h"

struct level_struct {
    unsigned short value;
    unsigned short max;

    level_struct() = default;

    level_struct(unsigned short _value, unsigned short _max)
    {
        value = _value;
        max = _max;
    }

    unsigned short numberOfSprites(unsigned short barWidth)
    {
        // BN_LOG("\n1 - numberOfSprites: ", bn::fixed(value).safe_division(max).safe_multiplication(bn::fixed(barWidth).safe_division(8).ceil_integer()).ceil_integer(), "\n2 - numberOfSprites: ", bn::fixed(value).safe_division(max).safe_multiplication(bn::fixed(barWidth).safe_division(8)).ceil_integer());
        return bn::fixed(value).safe_division(max).safe_multiplication(barWidth - 1).safe_division(8).ceil_integer();
    }

    unsigned short spriteIndex(unsigned short barWidth)
    {
        // BN_LOG("\nnumberOfSprites: ", numberOfSprites(barWidth), "\nraw - index: ", 8 - bn::fixed(value).safe_division(max).safe_multiplication(bn::fixed(barWidth).modulo(8)), " \nrnd - index: ", 8 - bn::fixed(value).safe_division(max).safe_multiplication(bn::fixed(barWidth).modulo(8)).round_integer(), "\ncei - index: ", 8 - bn::fixed(value).safe_division(max).safe_multiplication(bn::fixed(barWidth).modulo(8)).ceil_integer(), "\nflr - index: ", 8 - bn::fixed(value).safe_division(max).safe_multiplication(bn::fixed(barWidth).modulo(8)).floor_integer());
        // BN_LOG("\nnumberOfSprites: ", numberOfSprites(barWidth), "\nraw - index: ", 8 - bn::fixed(value).safe_division(max).safe_multiplication(barWidth).modulo(8), " \nrnd - index: ", 8 - bn::fixed(value).safe_division(max).safe_multiplication(barWidth).modulo(8).round_integer(), "\ncei - index: ", 8 - bn::fixed(value).safe_division(max).safe_multiplication(barWidth).modulo(8).ceil_integer(), "\nflr - index: ", 8 - bn::fixed(value).safe_division(max).safe_multiplication(barWidth).modulo(8).floor_integer());
        // BN_LOG("\nnumberOfSprites: ", numberOfSprites(barWidth), "\nraw - index: ", 8 - bn::fixed(numberOfSprites(barWidth)).modulo(8), " \nrnd - index: ", 8 - bn::fixed(numberOfSprites(barWidth)).modulo(8).round_integer(), "\ncei - index: ", 8 - bn::fixed(numberOfSprites(barWidth)).modulo(8).ceil_integer(), "\nflr - index: ", 8 - bn::fixed(numberOfSprites(barWidth)).modulo(8).floor_integer(), "\n\nraw - index: ", 7 - bn::fixed(numberOfSprites(barWidth)).modulo(8), " \nrnd - index: ", 7 - bn::fixed(numberOfSprites(barWidth)).modulo(8).round_integer(), "\ncei - index: ", 7 - bn::fixed(numberOfSprites(barWidth)).modulo(8).ceil_integer(), "\nflr - index: ", 7 - bn::fixed(numberOfSprites(barWidth)).modulo(8).floor_integer());
        // BN_LOG("\nvalue: ", value, "\nmax: ", max, "\n(v/m)*b: ", bn::fixed(value).safe_division(max).safe_multiplication(barWidth), "\n((v/m)*b)%8: ", bn::fixed(value).safe_division(max).safe_multiplication(barWidth).modulo(8), "\n7-((v/m)*b)%8: ", 7 - bn::fixed(value).safe_division(max).safe_multiplication(barWidth).modulo(8));
        // if (numberOfSprites(barWidth) == 30)
        // {
        //     BN_LOG("\nindex: ", 7 - bn::fixed(value).safe_division(max).safe_multiplication(barWidth).modulo(8).floor_integer());
        // }
        return 7 - bn::fixed(value).safe_division(max).safe_multiplication(barWidth - 1).modulo(8).floor_integer();
    }
};

#endif //LEVEL_STRUCT_H