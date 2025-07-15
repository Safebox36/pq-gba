#ifndef SPELL_STRUCT_H
#define SPELL_STRUCT_H

struct spell_struct {
    unsigned char id;
    unsigned char level;
    bool multiLine;

    spell_struct(unsigned char _id, unsigned char _level, bool _multiLine = false)
    {
        id = _id;
        level = _level;
        multiLine = _multiLine;
    }
};

#endif //SPELL_STRUCT_H