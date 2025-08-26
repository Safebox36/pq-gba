#ifndef LEVEL_STRUCT_H
#define LEVEL_STRUCT_H
#include "bn_log.h"

struct level_struct {
    unsigned short value;
    unsigned short max;

    level_struct() = default;

    level_struct(unsigned short _value, unsigned short _max)
    {
        value = _value;
        max = _max;
    }

    unsigned short numberOfSprites(unsigned short barWidth, unsigned short rounder)
    {
        auto base = bn::fixed(value).safe_division(max).safe_multiplication(rounder);
        auto remainder = bn::fixed(value).safe_division(max).safe_multiplication(barWidth).modulo(8);
        if (max == 120)
        {
            BN_LOG("\nremainder: ", remainder, " - ", remainder.floor_integer(), " - ", remainder.round_integer(), " - ", remainder.ceil_integer());
        }
        return remainder.ceil_integer() == 0 ? base.floor_integer() : base.ceil_integer();
    }

    unsigned short spriteIndex(unsigned short barWidth)
    {
        // auto adjusted = bn::fixed(barWidth).safe_division(adjusterB).safe_multiplication(value);
        auto base = bn::fixed(value).safe_division(max);
        auto adjusted = base.safe_multiplication(barWidth);
        auto remainder = adjusted.modulo(8);
// BN_LOG(adjusted.round_integer(), ":", (adjusted % modulo).floor_integer(), ":", (7 - (adjusted % modulo).floor_integer()));
        // BN_LOG("7 - (adjusted % modulo).floor_integer(): ", 7 - (adjusted % modulo).floor_integer(), ", 7 - (adjusted % modulo).round_integer(): ", 7 - (adjusted % modulo).round_integer(), ", 7 - (adjusted % modulo).ceil_integer(): ", 7 - (adjusted % modulo).ceil_integer());
        // BN_LOG(value, "/", max, " = ", bn::fixed(static_cast<float>(value) / static_cast<float>(max)), " - ", barWidth, "/", adjusterB, " = ", bn::fixed(static_cast<float>(barWidth) / static_cast<float>(adjusterB)));
        // BN_LOG(max, " * (", barWidth, "/", adjusterB, ") = ", max * bn::fixed(static_cast<float>(barWidth) / static_cast<float>(adjusterB)), " - ", bn::fixed(max * (static_cast<float>(barWidth) / static_cast<float>(adjusterB))), " (", bn::fixed(max * (static_cast<float>(barWidth) / static_cast<float>(adjusterB))).floor_integer(), ")");
        // BN_LOG((adjusted % modulo), " - ", 7 - (adjusted.floor_integer() % modulo), ":", 7 - (adjusted.round_integer() % modulo), ":", 7 - (adjusted.ceil_integer() % modulo), " - ", 7 - (adjusted % modulo).floor_integer(), ":", 7 - (adjusted % modulo).round_integer(), ":", 7 - (adjusted % modulo).ceil_integer());
        if (max == 120)
        {
            BN_LOG("\n", numberOfSprites(234, 30), " - ", 8 - adjusted.modulo(8).ceil_integer(), " - ", 8 - adjusted.modulo(8).integer(), " - ", 8 - adjusted.modulo(8));
            // BN_LOG("\n", value, "/", max, "\nnumberOfSprites: ", bn::fixed(value).safe_division(max).safe_multiplication(30), " - ", numberOfSprites(30), "\nadjusted: ", adjusted.integer(), " - ", adjusted.floor_integer(), ":", adjusted.round_integer(), ":", adjusted.ceil_integer(), "\nsprite: ", numberOfSprites(30), "\nindex: ", 7 - adjusted.modulo(modulo).integer(), " - ", 7 - adjusted.modulo(modulo).floor_integer(), ":", 7 - adjusted.modulo(modulo).round_integer(), ":", 7 - adjusted.modulo(modulo).ceil_integer());
            // BN_LOG("\n % ", adjusted, " - ", numberOfSprites(30), "\nsub - ", 7 - adjusted.modulo(7), ":", 8 - adjusted.modulo(7), "\nsub floor - ", 7 - adjusted.modulo(modulo).floor_integer(), ":", 8 - adjusted.modulo(modulo).floor_integer(), "\nsub round - ", 7 - adjusted.modulo(modulo).round_integer(), ":", 8 - adjusted.modulo(modulo).round_integer(), "\nsub ceil - ", 7 - adjusted.modulo(modulo).ceil_integer(), ":", 8 - adjusted.modulo(modulo).ceil_integer());
            // BN_LOG("\n % ", bn::fixed(value).safe_division(max), "\n - ", bn::fixed(value).modulo(modulo).integer(), "\n - ", bn::fixed(barWidth).safe_division(adjusterB).safe_multiplication(value).modulo(modulo).integer());
            // BN_LOG("\n - numberOfSprites(rounder): ", numberOfSprites(30), "\n - 7 - bn::fixed(adjusted.floor_integer()).modulo(modulo): ", 7  - bn::fixed(adjusted.floor_integer()).modulo(modulo), "\n - 7 - bn::fixed(adjusted.round_integer()).modulo(modulo): ", 7  - bn::fixed(adjusted.round_integer()).modulo(modulo), "\n - 7 - bn::fixed(adjusted.ceil_integer()).modulo(modulo): ", 7  - bn::fixed(adjusted.ceil_integer()).modulo(modulo));
            // BN_LOG("\n", adjusted, " - ", numberOfSprites(30), "\n - ", adjusted.floor_integer(), ":", adjusted.round_integer(), ":", adjusted.ceil_integer(), "\n - ", 7 - adjusted.modulo(modulo).floor_integer(), ":", 7 - adjusted.modulo(modulo).round_integer(), ":", 7 - adjusted.modulo(modulo).ceil_integer());
            // BN_LOG("\n", adjusted, "\n", adjusted.floor_integer(), ",", adjusted.round_integer(), ",", adjusted.ceil_integer(), "\n", 7 - adjusted.modulo(modulo).floor_integer(), ",", 7 - adjusted.modulo(modulo).round_integer(), ",", 7 - adjusted.modulo(modulo).ceil_integer());
        }
        return 8 - adjusted.modulo(8).ceil_integer();
    }
};

#endif //LEVEL_STRUCT_H