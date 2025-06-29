#ifndef FONT_H
#define FONT_H

#include "bn_sprite_font.h"

class font
{
    public:
        font();
        bn::sprite_font get();
        bn::sprite_font getBold();
};

#endif //FONT_H