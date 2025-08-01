#ifndef FONT_H
#define FONT_H

#include "bn_sprite_font.h"
#include "bn_sprite_items_font.h"
#include "bn_sprite_items_font_bold.h"
#include "bn_utf8_characters_map.h"

constexpr char font_regular_chars[] = {
    " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
};
constexpr int8_t font_regular_widths[] = {
    3, 2, 4, 7, 6, 8, 6, 2, 3, 3, 4, 6, 0, 6, 2, 5,
    6, 4, 6, 6, 6, 6, 6, 6, 6, 6, 2, 3, 6, 6, 6, 6,
    11, 8, 6, 7, 7, 6, 6, 7, 7, 2, 5, 7, 6, 8, 7, 7,
    7, 7, 7, 6, 6, 7, 8, 12, 8, 8, 8, 3, 5, 3, 6, 7,
    0, 6, 6, 6, 6, 6, 3, 6, 6, 2, 2, 6, 2, 8, 6, 6,
    6, 6, 3, 5, 3, 6, 6, 8, 5, 6, 5, 4, 2, 4, 7
};

// constexpr bn::span<const bn::utf8_character> regular_spans(chars);
// constexpr auto regular_map = bn::utf8_characters_map<regular_spans>();
constexpr auto font_regular = bn::sprite_font(bn::sprite_items::font, bn::utf8_characters_map_ref(), font_regular_widths);
constexpr auto font_bold = bn::sprite_font(bn::sprite_items::font_bold);

#endif //FONT_H