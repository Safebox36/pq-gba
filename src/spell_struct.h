#ifndef SPELL_STRUCT_H
#define SPELL_STRUCT_H

struct spell_struct {
    unsigned char id;
    unsigned char level;

    spell_struct(unsigned char _id, unsigned char _level)
    {
        id = _id;
        level = _level;
    }
};

#endif //SPELL_STRUCT_H