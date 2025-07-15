#ifndef EQUIPMENT_STRUCT_H
#define EQUIPMENT_STRUCT_H

struct equipment_struct {
    enum equip_type
    {
        weapon,
        shield,
        armour
    };

    unsigned char equipId;
    equip_type typeId;
    unsigned char modifierId;

    equipment_struct(unsigned char _equipId, equip_type _typeId, unsigned char _modifierId)
    {
        equipId = _equipId;
        typeId = _typeId;
        modifierId = _modifierId;
    }
};

#endif //EQUIPMENT_STRUCT_H