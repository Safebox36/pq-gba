#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "bn_rect_window.h"
#include "bn_vector.h"
#include "bn_fixed.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_string.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "player_struct.h"
#include "data_strings.h"

class game_controller
{
    private:
        int activeTab = 0;
        int highlightedScrollbar = 0;
        bn::optional<bn::regular_bg_item> background_1;
        bn::optional<bn::regular_bg_item> background_2;
        bn::optional<bn::regular_bg_item> background_3;
        bn::optional<bn::regular_bg_item> background_4;
        bn::optional<bn::regular_bg_ptr> active_background;

        bn::optional<bn::rect_window> tabs;
        bn::vector<bn::vector<bn::sprite_ptr, 8>, 4> titles;
        bn::optional<bn::sprite_text_generator> text_generator;
        bn::vector<bn::string_view, 4> title_strings;
        bn::optional<bn::sprite_item> scroll;
        bn::vector<bn::sprite_ptr, 4> scrollbars;
        bn::optional<bn::sprite_ptr> scroll_thumb;
        bn::vector<int, 2> scroll_values;
        bn::vector<bn::vector<bn::sprite_ptr, 32>, 2> player_data;
        bn::vector<bn::sprite_ptr, 32> player_data_labels;
        bn::vector<bn::sprite_ptr, 16> player_progress;
        bn::vector<bn::point, 2> player_data_default_positions;

        bn::vector<bn::string<32>, 61> spell_list;
        bn::vector<short, 11> spell_levels;
        bn::vector<bn::string<32>, 33> equip_list;

        int lerp(bn::fixed v0, bn::fixed v1, bn::fixed t);

    public:
        bool incrementActiveTab();
        bool decrementActiveTab();
        bool incrementHighlightedScrollbar(player_struct& player);
        bool decrementHighlightedScrollbar();

        void updateScrollbar(player_struct& player);
        void updateLists(player_struct& player, data_strings& data_strings);
        void drawTab1(player_struct& player, data_strings& data_strings);
        void drawTab2(player_struct& player, data_strings& data_strings);
        void drawTab3(player_struct& player, data_strings& data_strings);
        void drawTab4(player_struct& player, data_strings& data_strings);

        bool rome(unsigned int& n, unsigned int dn, bn::string<7>& s, bn::string<7> ds);
        bn::string<7> intToRome(unsigned int n);

        void enter(player_struct& player, data_strings& data_strings);
        void update(player_struct& player, data_strings& data_strings);
        void exit();
};

#endif //GAME_CONTROLLER_H