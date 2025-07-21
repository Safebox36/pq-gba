#ifndef GAME_STRUCT_H
#define GAME_STRUCT_H

#include "bn_string.h"

struct game_struct_t {
    unsigned char elapsed;

    bn::string<32> task;
    unsigned short act;
    unsigned short bestQuest;
    unsigned short bestPlot;

    unsigned short bestEquip;
    unsigned short bestSpell;
    unsigned short bestStat;

    bn::string<32> kill;
    unsigned short questMonster;

    game_struct_t() = default;

    game_struct_t(unsigned short _value, unsigned short _max)
    {
        value = _value;
        max = _max;
    }
};

#endif //GAME_STRUCT_H