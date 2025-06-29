#include "menu_controller.h"

#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_vector.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_menu_back.h"
#include "bn_regular_bg_items_menu_main.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_items_spr_button.h"
#include "bn_sprite_text_generator.h"
#include "font.h"

font regular_font;
bn::optional<bn::regular_bg_ptr> menu_desktop;
bn::optional<bn::regular_bg_ptr> menu_main;
bn::vector<bn::sprite_ptr, 2> button_new;
bn::vector<bn::sprite_ptr, 2> button_load;
bn::vector<bn::sprite_ptr, 32> text_sprites_new = bn::vector<bn::sprite_ptr, 2>();
bn::sprite_text_generator text_generator = bn::sprite_text_generator(regular_font.get());

int menu_controller::getSelectedOption() {
    return selectedOption;
}

void menu_controller::setSelectedOption(int option)
{
    selectedOption = option < 0 ? 0 : (option > 1 ? 1 : option);
}

void menu_controller::enter()
{
    regular_font = font();

    menu_desktop = bn::regular_bg_items::menu_back.create_bg();
    menu_desktop->set_top_left_position(0, 0);
    menu_main = bn::regular_bg_items::menu_main.create_bg();
    menu_main->set_top_left_position(0, 0);

    button_new = bn::vector<bn::sprite_ptr, 2>();
    button_new.push_back(bn::sprite_items::spr_button.create_sprite(2));
    button_new.push_back(bn::sprite_items::spr_button.create_sprite(3));
    button_load = bn::vector<bn::sprite_ptr, 2>();
    button_load.push_back(bn::sprite_items::spr_button.create_sprite(0));
    button_load.push_back(bn::sprite_items::spr_button.create_sprite(1));

    button_new[0].set_top_left_position(128, 56);
    button_new[1].set_top_left_position(128 + 32, 56);
    button_load[0].set_top_left_position(128, 80);
    button_load[1].set_top_left_position(128 + 32, 80);

    text_generator.set_center_alignment();
    text_generator.generate_top_left(128 + (56 / 2), 56, "ABC", text_sprites_new);
}

void menu_controller::update()
{
    if (bn::keypad::up_pressed())
    {
        setSelectedOption(0);
        button_new[0] = bn::sprite_items::spr_button.create_sprite(2);
        button_new[1] = bn::sprite_items::spr_button.create_sprite(3);
        button_load[0] = bn::sprite_items::spr_button.create_sprite(0);
        button_load[1] = bn::sprite_items::spr_button.create_sprite(1);

        button_new[0].set_top_left_position(128, 56);
        button_new[1].set_top_left_position(128 + 32, 56);
        button_load[0].set_top_left_position(128, 80);
        button_load[1].set_top_left_position(128 + 32, 80);
    }
    else if (bn::keypad::down_pressed())
    {
        setSelectedOption(1);
        button_new[0] = bn::sprite_items::spr_button.create_sprite(0);
        button_new[1] = bn::sprite_items::spr_button.create_sprite(1);
        button_load[0] = bn::sprite_items::spr_button.create_sprite(2);
        button_load[1] = bn::sprite_items::spr_button.create_sprite(3);

        button_new[0].set_top_left_position(128, 56);
        button_new[1].set_top_left_position(128 + 32, 56);
        button_load[0].set_top_left_position(128, 80);
        button_load[1].set_top_left_position(128 + 32, 80);
    }
}

void menu_controller::exit()
{
    menu_desktop.reset();
    menu_main.reset();
    button_new.clear();
    button_load.clear();
}