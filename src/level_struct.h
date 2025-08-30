#ifndef LEVEL_STRUCT_H
#define LEVEL_STRUCT_H

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
        return bn::fixed(value).safe_division(max).safe_multiplication(barWidth - 1).safe_division(8).ceil_integer();
    }

    unsigned short spriteIndex(unsigned short barWidth)
    {
        return 7 - bn::fixed(value).safe_division(max).safe_multiplication(barWidth - 1).modulo(8).floor_integer();
    }
};

#endif //LEVEL_STRUCT_H