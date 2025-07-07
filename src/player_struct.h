#ifndef PLAYER_STRUCT_H
#define PLAYER_STRUCT_H

#include <bn_vector.h>
#include <bn_string_view.h>
#include <bn_random.h>

struct player_struct
{
    unsigned short race_id = 0;
    unsigned short class_id = 0;

    bn::vector<unsigned int, 6> stats = bn::vector<unsigned int, 6>();
    bn::vector<bn::string_view, 6> stat_strings = bn::vector<bn::string_view, 6>();

    bn::random rng;

    player_struct()
    {
        rng = bn::random();

        stats = bn::vector<unsigned int, 6>();
        for (int i = 0; i < 6; i++)
        {
            stats.push_back(0);
        }
        stat_strings.push_back("STR");
        stat_strings.push_back("DEX");
        stat_strings.push_back("CON");
        stat_strings.push_back("INT");
        stat_strings.push_back("WIS");
        stat_strings.push_back("CHA");
    }

    void roll()
    {
        for (int i = 0; i < 6; i++)
        {
            stats[i] = 3 + rng.get_unbiased_int(6) + rng.get_unbiased_int(6) + rng.get_unbiased_int(6);
        }
    }

    void generateNewSeed()
    {
        rng.update();
    }
};

#endif //PLAYER_STRUCT_H