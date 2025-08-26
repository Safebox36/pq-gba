#ifndef PLAYER_STRUCT_H
#define PLAYER_STRUCT_H

#include "bn_fixed.h"
#include "bn_vector.h"
#include "bn_deque.h"
#include "bn_random.h"
#include "spell_struct.h"
#include "equipment_struct.h"
#include "item_struct.h"
#include "level_struct.h"
#include "quest_struct.h"
#include "progress_struct.h"
#include "tq_struct.h"

struct player_struct
{
    unsigned short race_id = 0;
    unsigned short class_id = 0;
    unsigned short level = 1;

    bn::vector<unsigned int, 8> stats = bn::vector<unsigned int, 8>();
    bn::vector<spell_struct, 45> spells = bn::vector<spell_struct, 45>();
    bn::vector<equipment_struct, 11> equipment = bn::vector<equipment_struct, 11>();
    bn::vector<item_struct, 255> inventory = bn::vector<item_struct, 255>();

    tq_struct task_data = tq_struct("", 0);
    tq_struct quest_data = tq_struct("", 0);
    level_struct task_prog = level_struct(0, 1);
    level_struct quest_prog = level_struct(0, 1);
    level_struct plot_prog = level_struct(0, 1);
    level_struct exp = level_struct(0, 1);
    level_struct enc = level_struct(0, 1);
    bn::deque<quest_struct, 16> quest_queue = bn::deque<quest_struct, 16>();
    bn::deque<quest_struct, 16> plot_queue = bn::deque<quest_struct, 16>();
    bn::deque<progress_struct, 8> message_queue = bn::deque<progress_struct, 8>();
    bn::string<128> kill = bn::string<128>();

    bn::random rng = bn::random();
    unsigned char elapsed = 0;
    unsigned char ticker_offset = 0;

    player_struct()
    {
        for (int i = 0; i < 8; i++)
        {
            stats.push_back(0);
        }

        inventory.push_back(item_struct(0, item_struct::gold, 0, 0, 0, 0));
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
        enc.max = stats[0] + 10;
    }

    void generateNewSeed()
    {
        rng.update();
    }
};

#endif //PLAYER_STRUCT_H