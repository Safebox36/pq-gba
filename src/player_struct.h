#ifndef PLAYER_STRUCT_H
#define PLAYER_STRUCT_H

#include "bn_vector.h"
#include "bn_random.h"
#include "spell_struct.h"
#include "equipment_struct.h"

struct player_struct
{
    unsigned short race_id = 0;
    unsigned short class_id = 0;
    unsigned short level = 0;

    bn::vector<unsigned int, 8> stats;
    bn::vector<spell_struct, 45> spells;
    bn::vector<equipment_struct, 11> equipment;

    bn::random rng;

    player_struct()
    {
        rng = bn::random();

        stats = bn::vector<unsigned int, 8>();
        for (int i = 0; i < 8; i++)
        {
            stats.push_back(0);
        }

        spells = bn::vector<spell_struct, 45>();
        equipment = bn::vector<equipment_struct, 11>();
    }

    void roll()
    {
        for (int i = 0; i < 6; i++)
        {
            stats[i] = 3 + rng.get_unbiased_int(6) + rng.get_unbiased_int(6) + rng.get_unbiased_int(6);
        }
        for (int i = 0; i < 2; i++)
        {
            stats[6 + i] = (bn::fixed(stats[2 + i] / 6.f) + rng.get_unbiased_int(8)).round_integer();
        }
    }

    void generateNewSeed()
    {
        rng.update();
    }
};

#endif //PLAYER_STRUCT_H