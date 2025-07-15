#include "menu_controller.h"

#include "bn_keypad.h"
#include "bn_vector.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_menu_back.h"
#include "bn_regular_bg_items_menu_main.h"
#include "bn_regular_bg_items_menu_load.h"
#include "bn_regular_bg_animate_actions.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_items_spr_button.h"
#include "bn_sprite_text_generator.h"
#include "font.h"

void menu_controller::setSelectedOption(int option)
{
    selectedOption = option < 0 ? 0 : (option > 1 ? 1 : option);
}

void menu_controller::enter()
{
    menu_desktop = bn::regular_bg_items::menu_back.create_bg();
    menu_desktop->set_top_left_position(0, 0);
    menu_main = bn::regular_bg_items::menu_main.create_bg();
    menu_main->set_top_left_position(0, 0);

    button_new = bn::vector<bn::sprite_ptr, 5>();
    button_load = bn::vector<bn::sprite_ptr, 5>();
    for (int i = 0; i < 5; i++)
    {
        switch (i)
        {
            case 0:
                button_new.push_back(bn::sprite_items::spr_button.create_sprite(3));
                button_load.push_back(bn::sprite_items::spr_button.create_sprite(0));
                break;
            case 4:
                button_new.push_back(bn::sprite_items::spr_button.create_sprite(5));
                button_load.push_back(bn::sprite_items::spr_button.create_sprite(2));
                break;
            default:
                button_new.push_back(bn::sprite_items::spr_button.create_sprite(4));
                button_load.push_back(bn::sprite_items::spr_button.create_sprite(1));
                break;
        }
        button_new[i].set_top_left_position(116 + (i * 16), 52);
        button_load[i].set_top_left_position(116 + (i * 16), 84);
    }

    text_sprites =  bn::vector<bn::sprite_ptr, 4>();
    text_generator = bn::sprite_text_generator(font_regular);
    text_generator->set_center_alignment();
    text_generator->generate_top_left(button_new[0].top_left_position() + bn::fixed_point(80 / 2, 6), "New Game", text_sprites);
    text_generator->generate_top_left(button_load[0].top_left_position() + bn::fixed_point(80 / 2, 6), "Load Game", text_sprites);
    for (auto c : text_sprites)
    {
        c.set_z_order(-10);
    }
}

void menu_controller::update(int& nextScreen)
{
    if (isLoading)
    {
        if (loading_screen.has_value() == false)
        {
            loading_screen = bn::regular_bg_items::menu_load.create_bg();
            loading_screen->set_priority(0);
            loading_screen->set_top_left_position(0, 0);
            loading_animation = bn::create_regular_bg_animate_action_once(loading_screen.value(), 0, bn::regular_bg_items::menu_load.map_item(), 0, 1, 2, 3);
        }
        else if (loading_animation.value().done())
        {
            switch (selectedOption)
            {
                case 0:
                    nextScreen = 1;
                    exit();
                    break;
                case 1:
                    break;
            }
        }
        else
        {
            loading_animation.value().update();
        }
        return;
    }

    if (bn::keypad::a_pressed())
    {
        isLoading = true;
    }
    else if (bn::keypad::up_pressed())
    {
        setSelectedOption(0);
        for (int i = 0; i < 5; i++)
        {
            switch (i)
            {
                case 0:
                    button_new[i] = bn::sprite_items::spr_button.create_sprite(3);
                    button_load[i] = bn::sprite_items::spr_button.create_sprite(0);
                    break;
                case 4:
                    button_new[i] = bn::sprite_items::spr_button.create_sprite(5);
                    button_load[i] = bn::sprite_items::spr_button.create_sprite(2);
                    break;
                default:
                    button_new[i] = bn::sprite_items::spr_button.create_sprite(4);
                    button_load[i] = bn::sprite_items::spr_button.create_sprite(1);
                    break;
            }
            button_new[i].set_top_left_position(116 + (i * 16), 52);
            button_load[i].set_top_left_position(116 + (i * 16), 84);
        }
    }
    else if (bn::keypad::down_pressed())
    {
        setSelectedOption(1);
        for (int i = 0; i < 5; i++)
        {
            switch (i)
            {
                case 0:
                    button_new[i] = bn::sprite_items::spr_button.create_sprite(0);
                    button_load[i] = bn::sprite_items::spr_button.create_sprite(3);
                    break;
                case 4:
                    button_new[i] = bn::sprite_items::spr_button.create_sprite(2);
                    button_load[i] = bn::sprite_items::spr_button.create_sprite(5);
                    break;
                default:
                    button_new[i] = bn::sprite_items::spr_button.create_sprite(1);
                    button_load[i] = bn::sprite_items::spr_button.create_sprite(4);
                    break;
            }
            button_new[i].set_top_left_position(116 + (i * 16), 52);
            button_load[i].set_top_left_position(116 + (i * 16), 84);
        }
    }
}

void menu_controller::exit()
{
    menu_desktop.reset();
    menu_main.reset();
    button_new.clear();
    button_load.clear();
    text_sprites.clear();
    text_generator.reset();
    loading_animation.reset();
    loading_screen.reset();
}