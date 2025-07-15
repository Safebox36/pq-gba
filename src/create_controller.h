#ifndef CREATE_CONTROLLER_H
#define CREATE_CONTROLLER_H

#include "bn_rect_window.h"
#include "bn_vector.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "player_struct.h"
#include "data_strings.h"

class create_controller
{
    private:
        int activeTab = 0;
        bn::rect highlightedOption = bn::rect(0, 0, 0, 0);
        bn::optional<bn::regular_bg_item> background_1;
        bn::optional<bn::regular_bg_item> background_2;
        bn::optional<bn::regular_bg_item> background_3;
        bn::optional<bn::regular_bg_item> background_4;
        bn::optional<bn::regular_bg_ptr> active_background;

        bn::optional<bn::rect_window> tabs;
        bn::vector<bn::vector<bn::sprite_ptr, 8>, 4> titles;
        bn::optional<bn::sprite_text_generator> text_generator;
        bn::vector<bn::string_view, 4> title_strings;
        bn::optional<bn::sprite_item> bullet;
        bn::vector<bn::sprite_ptr, 16> bullets;
        bn::vector<bn::sprite_ptr, 48> bullet_titles;
        bn::optional<bn::sprite_item> stat;

    public:
        bool incrementActiveTab();
        bool decrementActiveTab();
        bool incrementHighlightedOptionX();
        bool decrementHighlightedOptionX();
        bool incrementHighlightedOptionY();
        bool decrementHighlightedOptionY();

        void updateBullets(player_struct& player, bool refreshAll = false);
        void updateLabels(player_struct& player, data_strings& data_strings);
        void drawTab1(player_struct& player, data_strings& data_strings);
        void drawTab2(player_struct& player, data_strings& data_strings);
        void drawTab3(player_struct& player, data_strings& data_strings);
        void drawTab4(player_struct& player, data_strings& data_strings);

        void rome(unsigned int n, unsigned int dn, bn::string_view& s, bn::string_view& sn);

        void enter(player_struct& player, data_strings& data_strings);
        void update(int& nextScreen, player_struct& player, data_strings& data_strings);
        void exit();
};

#endif //CREATE_CONTROLLER_H