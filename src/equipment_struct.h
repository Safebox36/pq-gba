#ifndef EQUIPMENT_STRUCT_H
#define EQUIPMENT_STRUCT_H

struct equipment_struct
{
    enum equip_type
    {
        weapon,
        shield,
        armour,
        dummy
    };

    unsigned char equipId;
    equip_type typeId;
    unsigned char modifierId;

    equipment_struct(unsigned char _equipId, equip_type _typeId, unsigned char _modifierId = 0)
    {
        equipId = _equipId;
        typeId = _typeId;
        modifierId = _modifierId;
    }
};

#endif //EQUIPMENT_STRUCT_H