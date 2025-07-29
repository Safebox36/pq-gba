#ifndef PROGRESS_STRUCT_H
#define PROGRESS_STRUCT_H

#include "bn_string.h"

struct progress_struct
{
    enum progress_type
    {
        task,
        plot,
    };

    progress_type typeId;
    unsigned char duration;
    bn::string<128> message;

    progress_struct(progress_type _typeId, unsigned char _duration, bn::string<128> _message)
    {
        typeId = _typeId;
        duration = _duration;
        message = _message;
    }
};

#endif //PROGRESS_STRUCT_H