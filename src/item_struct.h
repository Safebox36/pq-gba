#ifndef ITEM_STRUCT_H
#define ITEM_STRUCT_H

struct item_struct
{
    enum item_type
    {
        boring,
        monster,
        interesting,
        special,
        gold
    };

    unsigned short id;
    item_type typeId;
    unsigned char modifierId;
    unsigned char ofId;
    unsigned char level;
    unsigned short count;

    item_struct(unsigned short _id, item_type _typeId, unsigned _modifierId = 0, unsigned _ofId = 0, unsigned char _level = 0, unsigned short _count = 1)
    {
        id = _id;
        typeId = _typeId;
        modifierId = _modifierId;
        ofId = _ofId;
        level = _level;
        count = _count;
    }
};

#endif //ITEM_STRUCT_H