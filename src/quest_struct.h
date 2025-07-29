#ifndef QUEST_STRUCT_H
#define QUEST_STRUCT_H

#include "bn_string.h"

struct quest_struct {
    bn::string<128> desc;
    bool complete;

    quest_struct(bn::string<128> _desc)
    {
        desc = _desc;
        complete = false;
    }
};

#endif //QUEST_STRUCT_H