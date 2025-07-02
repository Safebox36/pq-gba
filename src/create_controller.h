#ifndef CREATE_CONTROLLER_H
#define CREATE_CONTROLLER_H

#include "bn_rect_window.h"
#include "bn_vector.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

class create_controller
{
    private:
        int activeTab = 0;
        int highlightedOption = 0;
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
        bn::vector<bn::sprite_ptr, 12> bullets;
        bn::vector<bn::sprite_ptr, 24> bullet_titles;
        bn::vector<bn::string_view, 21> race_strings;

    public:
        bool incrementActiveTab();
        bool decrementActiveTab();
        bool incrementHighlightedOption();
        bool decrementHighlightedOption();

        void enter();
        void update(int& activeScreen);
        void exit();
};

#endif //CREATE_CONTROLLER_H