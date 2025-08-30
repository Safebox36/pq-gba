#ifndef FONT_H
#define FONT_H

#include "bn_sprite_font.h"
#include "bn_sprite_items_font.h"
#include "bn_sprite_items_bold_font.h"
#include "bn_utf8_characters_map.h"

constexpr char font_regular_chars[] = {
    " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
};
constexpr int8_t font_regular_widths[] = {
    3, 2, 4, 7, 6, 8, 6, 2, 3, 3, 4, 6, 5, 6, 2, 5,
    6, 4, 6, 6, 6, 6, 6, 6, 6, 6, 2, 3, 6, 6, 6, 6,
    11, 8, 6, 7, 7, 6, 6, 7, 7, 2, 5, 7, 6, 8, 7, 7,
    7, 7, 7, 6, 6, 7, 8, 12, 8, 8, 8, 3, 5, 3, 6, 7,
    0, 6, 6, 6, 6, 6, 3, 6, 6, 2, 2, 6, 2, 8, 6, 6,
    6, 6, 3, 5, 3, 6, 6, 8, 5, 6, 5, 4, 2, 4, 7
};
constexpr int8_t font_bold_widths[] = {
    4, 3, 5, 8, 7, 9, 7, 3, 4, 4, 5, 7, 6, 7, 3, 6,
    7, 5, 7, 7, 7, 7, 7, 7, 7, 7, 3, 4, 7, 7, 7, 7,
    12, 9, 7, 8, 8, 7, 7, 8, 8, 3, 6, 8, 7, 9, 8, 8,
    8, 8, 8, 7, 7, 8, 9, 13, 9, 9, 9, 4, 6, 4, 7, 8,
    1, 7, 7, 7, 7, 7, 4, 7, 7, 3, 3, 7, 3, 9, 7, 7,
    7, 7, 4, 6, 4, 7, 7, 9, 6, 7, 6, 5, 3, 5, 8
};

// constexpr bn::span<const bn::utf8_character> regular_spans(chars);
// constexpr auto regular_map = bn::utf8_characters_map<regular_spans>();
constexpr auto font_regular = bn::sprite_font(bn::sprite_items::font, bn::utf8_characters_map_ref(), font_regular_widths);
constexpr auto font_bold = bn::sprite_font(bn::sprite_items::bold_font, bn::utf8_characters_map_ref(), font_bold_widths);

#endif //FONT_H