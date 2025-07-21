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
};

#endif //LEVEL_STRUCT_H