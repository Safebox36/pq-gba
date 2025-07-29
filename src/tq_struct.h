#ifndef TASK_STRUCT_H
#define TASK_STRUCT_H

#include "bn_string.h"

struct tq_struct
{
    bn::string<128> caption;
    unsigned short tag;
    bn::optional<item_struct> reward;

    tq_struct(bn::string<128> _caption, unsigned short _tag)
    {
        caption = _caption;
        tag = _tag;
    }
};

#endif //TASK_STRUCT_H