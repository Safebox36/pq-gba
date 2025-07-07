#ifndef CREATE_CONTROLLER_H
#define CREATE_CONTROLLER_H

#include "bn_rect_window.h"
#include "bn_vector.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "player_struct.h"

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
        bn::vector<bn::string_view, 21> race_strings;
        bn::vector<bn::string_view, 18> class_strings;
        bn::optional<bn::sprite_item> stat;

    public:
        bool incrementActiveTab();
        bool decrementActiveTab();
        bool incrementHighlightedOptionX();
        bool decrementHighlightedOptionX();
        bool incrementHighlightedOptionY();
        bool decrementHighlightedOptionY();

        void updateBullets(player_struct& player, bool refreshAll = false);
        void updateLabels(player_struct& player);
        void drawTab1(player_struct& player);
        void drawTab2(player_struct& player);
        void drawTab3(player_struct& player);
        void drawTab4(player_struct& player);

        void enter(player_struct& player);
        void update(int& activeScreen, player_struct& player);
        void exit();
};

#endif //CREATE_CONTROLLER_H