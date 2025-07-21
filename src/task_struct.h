#ifndef TASK_STRUCT_H
#define TASK_STRUCT_H

#include "bn_string.h"

struct task_struct
{
    enum task_type
    {
        kill,
        buying,
        market,
        sell
    };

    task_type typeId;
    bn::string<32> desc;
    unsigned short num_data;
    bn::string<32> extra_data;

    task_struct(task_type _typeId, bn::string<32> _desc = "", unsigned short _num_data = 0, bn::string<32> _extra_data = "")
    {
        typeId = _typeId;
        desc = _desc;
        num_data = _num_data;
        extra_data = _extra_data;
    }
};

#endif //TASK_STRUCT_H