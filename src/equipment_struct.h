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
    enum modifier_type
    {
        good,
        bad
    };

    unsigned char equipId;
    equip_type baseEquipTypeId;
    equip_type modifierEquipTypeId;
    unsigned char modifierId1;
    modifier_type modifierTypeId1;
    bool hasModifier2;
    unsigned char modifierId2;
    modifier_type modifierTypeId2;
    signed char plusMinus;

    equipment_struct(unsigned char _equipId, equip_type _typeId, equip_type _modifierTypeId = dummy, unsigned char _modifierId1 = 0, modifier_type _modifierTypeId1 = good, bool _hasModifier2 = false, unsigned char _modifierId2 = 0, modifier_type _modifierTypeId2 = good)
    {
        equipId = _equipId;
        baseEquipTypeId = _typeId;
        modifierEquipTypeId = _modifierTypeId;
        modifierId1 = _modifierId1;
        modifierTypeId1 = _modifierTypeId1;
        hasModifier2 = _hasModifier2;
        modifierId2 = _modifierId2;
        modifierTypeId2 = _modifierTypeId2;
        plusMinus = 0;
    }
};

#endif //EQUIPMENT_STRUCT_H