#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "bn_vector.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_animate_actions.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

class menu_controller
{
    private:
        int selectedOption = 0;
        bn::optional<bn::regular_bg_ptr> menu_desktop;
        bn::optional<bn::regular_bg_ptr> menu_main;
        bn::vector<bn::sprite_ptr, 5> button_new;
        bn::vector<bn::sprite_ptr, 5> button_load;
        bn::vector<bn::sprite_ptr, 2> trademarks;
        bn::vector<bn::sprite_ptr, 4> text_sprites;
        bn::optional<bn::sprite_text_generator> text_generator;

        bool isLoading = false;
        bn::optional<bn::regular_bg_ptr> loading_screen;
        bn::optional<bn::regular_bg_animate_action<4>> loading_animation;

    public:
        void setSelectedOption(int option);

        void enter();
        void update(int& nextScreen);
        void exit();
};

#endif //MENU_CONTROLLER_H