#include "create_controller.h"

#include "bn_keypad.h"
#include "bn_rect_window.h"
#include "bn_vector.h"
#include "bn_regular_bg_items_scr_create_1.h"
#include "bn_regular_bg_items_scr_create_2.h"
#include "bn_regular_bg_items_scr_create_3.h"
#include "bn_regular_bg_items_scr_create_4.h"
#include "bn_sprite_items_spr_button.h"
#include "bn_sprite_items_spr_bullet.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "font.h"

bool create_controller::incrementActiveTab()
{
    if (activeTab == 3)
    {
        return false;
    }
    else
    {
        activeTab++;
        return true;
    }
}

bool create_controller::decrementActiveTab()
{
    if (activeTab == 0)
    {
        return false;
    }
    else
    {
        activeTab--;
        return true;
    }
}

bool create_controller::incrementHighlightedOption()
{
    switch (activeTab)
    {
        case 0:
            if (highlightedOption == 15)
            {
                return false;
            }
            else
            {
                highlightedOption++;
                return true;
            }
        case 1:
            if (highlightedOption == 4)
            {
                return false;
            }
            else
            {
                highlightedOption++;
                return true;
            }
    }
}

bool create_controller::decrementHighlightedOption()
{
    if (highlightedOption == 0)
    {
        return false;
    }
    else
    {
        highlightedOption--;
        return true;
    }
}

void create_controller::enter()
{
    background_1 = bn::regular_bg_items::scr_create_1;
    background_2 = bn::regular_bg_items::scr_create_2;
    background_3 = bn::regular_bg_items::scr_create_3;
    background_4 = bn::regular_bg_items::scr_create_4;
    active_background = background_1->create_bg();
    active_background->set_top_left_position(0, 0);

    tabs = bn::rect_window::internal();
    tabs->set_boundaries(-80 + 11, -120, 4 - 80 + 11, 240 - 120);
    tabs->set_show_sprites(false);
    titles = bn::vector<bn::vector<bn::sprite_ptr, 8>, 4>();
    for (int i = 0; i < 4; i++)
    {
        titles.push_back(bn::vector<bn::sprite_ptr, 8>());
    }
    title_strings = bn::vector<bn::string_view, 4>();
    title_strings.push_back("Races 1");
    title_strings.push_back("Races 2");
    title_strings.push_back("Cls/Sts");
    title_strings.push_back("Summary");

    bullet = bn::sprite_items::spr_bullet;
    race_strings = bn::vector<bn::string_view, 21>();
    race_strings.push_back("Half Orc");
    race_strings.push_back("Half Man");
    race_strings.push_back("Half Halfling");
    race_strings.push_back("Double Hobbit");
    race_strings.push_back("Gobhobbit");
    race_strings.push_back("Low Elf");
    race_strings.push_back("Dung Elf");
    race_strings.push_back("Talking Pony");
    race_strings.push_back("Gyrognome");
    race_strings.push_back("Lesser Dwarf");
    race_strings.push_back("Crested Dwarf");
    race_strings.push_back("Eel Man");
    race_strings.push_back("Panda Man");
    race_strings.push_back("Trans-Kobold");
    race_strings.push_back("Enchanted Motorcycle");
    race_strings.push_back("Will o' the Wisp");
    race_strings.push_back("Battle-Finch");
    race_strings.push_back("Double Wookiee");
    race_strings.push_back("Skraeling");
    race_strings.push_back("Demicanadian");
    race_strings.push_back("Land Squid");

    text_generator = bn::sprite_text_generator(font_regular);
    text_generator->set_center_alignment();
    for (int i = 0; i < 4; i++)
    {
        text_generator->generate_top_left(36 + (i * 7 * 8), i == 0 ? 0 : 2, title_strings[i], titles[i]);
        for (auto c : titles[i])
        {
            c.set_z_order(-10);
        }
    }
    for (int i = 0; i < 8; i++)
    {
        bullets.push_back(bullet->create_sprite(i == 0 ? 3 : 0));
        bullets[i].set_top_left_position(8, 20 + (i * 16));
    }
}

void create_controller::update(int& activeScreen)
{
    if (bn::keypad::a_pressed())
    {
        // switch (activeTab)
        // {
        //     case 0:
        //         exit();
        //         break;
        //     case 1:
        //         exit();
        //         break;
        // }
    }
    else if (bn::keypad::up_pressed())
    {
        decrementHighlightedOption();
        bullets[highlightedOption] = bullet->create_sprite(2);
        bullets[highlightedOption + 1] = bullet->create_sprite(0);
        bullets[highlightedOption].set_top_left_position(8, 20 + (highlightedOption * 16));
        bullets[highlightedOption + 1].set_top_left_position(8, 20 + ((highlightedOption + 1) * 16));
    }
    else if (bn::keypad::down_pressed())
    {
        incrementHighlightedOption();
        bullets[highlightedOption] = bullet->create_sprite(2);
        bullets[highlightedOption - 1] = bullet->create_sprite(0);
        bullets[highlightedOption].set_top_left_position(8, 20 + (highlightedOption * 16));
        bullets[highlightedOption - 1].set_top_left_position(8, 20 + ((highlightedOption - 1) * 16));
    }
    else if (bn::keypad::r_pressed())
    {
        if (incrementActiveTab())
        {
            switch (activeTab)
            {
                case 1:
                    active_background = background_2->create_bg();
                    break;
                case 2:
                    active_background = background_3->create_bg();
                    break;
                case 3:
                    active_background = background_4->create_bg();
                    break;
            }
            active_background->set_top_left_position(0, 0);
            for (int i = 0; i < 4; i++)
            {
                for (auto c : titles[i])
                {
                    c.set_top_left_y(i == activeTab ? 0 : 2);
                }
                if (activeTab == 3 and i == 3)
                {
                    tabs->set_right(tabs->right() - 32);
                }
            }
        }
    }
    else if (bn::keypad::l_pressed())
    {
        if (decrementActiveTab())
        {
            switch (activeTab)
            {
                case 0:
                    active_background = background_1->create_bg();
                    break;
                case 1:
                    active_background = background_2->create_bg();
                    break;
                case 2:
                    active_background = background_3->create_bg();
                    break;
            }
            active_background->set_top_left_position(0, 0);
            for (int i = 0; i < 4; i++)
            {
                for (auto c : titles[i])
                {
                    c.set_top_left_y(i == activeTab ? 0 : 2);
                }
                if (activeTab == 2 and i == 2)
                {
                    tabs->set_right(tabs->right() + 32);
                }
            }
        }
    }
}
//
// void create_controller::exit()
// {
//     create_desktop.reset();
//     create_main.reset();
//     button_new.clear();
//     button_load.clear();
// }