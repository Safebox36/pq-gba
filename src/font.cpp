#include "font.h"

#include "bn_optional.h"
#include "bn_sprite_font.h"
#include "bn_sprite_items_font.h"
#include "bn_sprite_items_font_bold.h"
#include "bn_utf8_characters_map.h"

bn::optional<bn::sprite_font> out_font;
bn::optional<bn::sprite_font> out_font_bold;

font::font()
{
    constexpr bn::utf8_character chars[] = {
        " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
    };
    int8_t widths[] = {
        0, 1, 3, 6, 5, 7, 5, 1, 2, 2, 3, 5, 0, 5, 1, 4,
        5, 3, 5, 5, 5, 5, 5, 5, 5, 5, 1, 2, 5, 5, 5, 5,
        10, 7, 5, 6, 6, 5, 5, 6, 6, 1, 4, 6, 5, 7, 6, 6,
        6, 6, 6, 5, 5, 6, 7, 11, 7, 7, 7, 2, 4, 2, 5, 6,
        0, 5, 5, 5, 5, 5, 2, 5, 5, 1, 1, 5, 1, 7, 5, 5,
        5, 5, 2, 4, 2, 5, 5, 7, 4, 5, 4, 3, 1, 3, 6
    };

    out_font = bn::sprite_font(bn::sprite_items::font);
    out_font_bold = bn::sprite_font(bn::sprite_items::font_bold);
}

bn::sprite_font font::get()
{
    return out_font.value();
}

bn::sprite_font font::getBold()
{
    return out_font_bold.value();
}