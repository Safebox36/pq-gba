#ifndef PLAYER_STRUCT_H
#define PLAYER_STRUCT_H

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
    unsigned short level = 0;

    bn::vector<unsigned int, 8> stats;
    bn::vector<spell_struct, 45> spells;
    bn::vector<equipment_struct, 11> equipment;
    bn::vector<item_struct, 1> inventory;

    tq_struct task_data = tq_struct("", 0);
    tq_struct quest_data = tq_struct("", 0);
    level_struct task_prog = level_struct(0, 1);
    level_struct quest_prog = level_struct(0, 1);
    level_struct exp = level_struct(0, 1);
    level_struct enc = level_struct(0, 1);
    level_struct plot = level_struct(0, 1);
    // level_struct quest;
    bn::deque<quest_struct, 16> quest_queue = bn::deque<quest_struct, 16>();
    bn::deque<quest_struct, 16> plot_queue = bn::deque<quest_struct, 16>();
    // unsigned char task = 0;
    bn::deque<progress_struct, 8> message_queue = bn::deque<progress_struct, 8>();
    // level_struct progress;

    bn::random rng;
    unsigned char elapsed;

    player_struct()
    {
        rng = bn::random();
        elapsed = 0;

        stats = bn::vector<unsigned int, 8>();
        for (int i = 0; i < 8; i++)
        {
            stats.push_back(0);
        }

        spells = bn::vector<spell_struct, 45>();
        equipment = bn::vector<equipment_struct, 11>();
        inventory = bn::vector<item_struct, 1>();

        // enc = level_struct(0, 1);
        // quest = level_struct(0, 1);
        // quest_queue = bn::deque<quest_struct, 16>();
        // message_queue = bn::deque<progress_struct, 8>();
        // progress = level_struct(0, 1);
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