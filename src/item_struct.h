#ifndef ITEM_STRUCT_H
#define ITEM_STRUCT_H

struct item_struct
{
    enum item_type
    {
        boring,
        monster,
        special,
        gold
    };

    unsigned short id;
    item_type typeId;
    unsigned char specialId;
    unsigned char modifierId;
    unsigned char ofId;
    unsigned char level;
    unsigned short count;

    item_struct(unsigned short _id, item_type _typeId, unsigned _specialId = 0, unsigned _modifierId = 0, unsigned _ofId = 0, unsigned char _level = 0, unsigned short _count = 1)
    {
        id = _id;
        typeId = _typeId;
        specialId = _specialId;
        modifierId = _modifierId;
        ofId = _ofId;
        level = _level;
        count = _count;
    }
};

#endif //ITEM_STRUCT_H