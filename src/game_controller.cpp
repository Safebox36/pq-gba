#include "game_controller.h"

#include "bn_keypad.h"
#include "bn_vector.h"
#include "bn_fixed.h"
#include "bn_regular_bg_items_scr_stats.h"
#include "bn_regular_bg_items_scr_equip.h"
#include "bn_regular_bg_items_scr_inv.h"
#include "bn_regular_bg_items_scr_main.h"
#include "bn_sprite_items_spr_scroll.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "font.h"
#include "player_struct.h"
#include "data_strings.h"

int game_controller::lerp(bn::fixed v0, bn::fixed v1, bn::fixed t)
{
    return (v0 + t * (v1 - v0)).round_integer();
}

bool game_controller::incrementActiveTab()
{
    if (activeTab == 3)
    {
        return false;
    }
    activeTab++;
    highlightedScrollbar = 0;
    return true;
}

bool game_controller::decrementActiveTab()
{
    if (activeTab == 0)
    {
        return false;
    }
    activeTab--;
    highlightedScrollbar = 0;
    return true;
}

bool game_controller::incrementHighlightedScrollbar(player_struct& player)
{
    switch (activeTab)
    {
        case 0:
            if (scroll_values[highlightedScrollbar] == player.stats.size() - 4)
            {
                return false;
            }
            break;
        case 1:
            if (highlightedScrollbar == 0)
            {
                if (spell_list.size() == 0 || scroll_values[highlightedScrollbar] == spell_list.size() - 5)
                {
                    return false;
                }
            }
            else if (highlightedScrollbar == 1)
            {
                if (equip_list.size() == 0 || scroll_values[highlightedScrollbar] == equip_list.size() - 6)
                {
                    return false;
                }
            }
            break;
    }
    scroll_values[highlightedScrollbar]++;
    return true;
}

bool game_controller::decrementHighlightedScrollbar()
{
    if (scroll_values[highlightedScrollbar] == 0)
    {
        return false;
    }
    scroll_values[highlightedScrollbar]--;
    return true;
}

void game_controller::updateScrollbar(player_struct& player)
{
    bn::point scrollPos;
    switch (activeTab)
    {
        case 0:
            scrollPos = bn::point(216, lerp(scrollbars[0].top_left_position().y() + 16, scrollbars[1].top_left_y() - 16, static_cast<float>(scroll_values[highlightedScrollbar]) / (player.stats.size() - 4)));
            break;
        case 1:
            if (highlightedScrollbar == 0)
            {
                scrollPos = bn::point(100, lerp(scrollbars[0].top_left_position().y() + 16, scrollbars[1].top_left_y() - 16, static_cast<float>(scroll_values[highlightedScrollbar]) / (spell_list.size() - 5)));
            }
            else if (highlightedScrollbar == 1)
            {
                scrollPos = bn::point(216, lerp(scrollbars[2].top_left_position().y() + 16, scrollbars[3].top_left_y() - 16, static_cast<float>(scroll_values[highlightedScrollbar]) / (equip_list.size() - 6)));
            }
            break;
    }
    scroll_thumb->set_top_left_position(scrollPos);
}

void game_controller::updateLists(player_struct& player, data_strings& data_strings)
{
    spell_list.clear();
    spell_levels.clear();
    for (auto spell : player.spells)
    {
        auto data = bn::string_view(data_strings.spells[spell.id]);
        if (spell.multiLine)
        {
            auto firstLine = data.substr(0, data.find('/'));
            auto secondLine = data.substr(data.find('/') + 1);
            spell_list.push_back(firstLine);
            spell_list.push_back(secondLine);
            spell_levels.push_back(0);
            spell_levels.push_back(spell.level);
        }
        else
        {
            spell_list.push_back(data);
            spell_levels.push_back(spell.level);
        }
    }

    for (int i = 0; i < data_strings.equipment_titles.size(); i++)
    {
        equip_list.push_back(data_strings.equipment_titles[i]);
        if (player.equipment.size() > i)
        {
            // bn::string<32> data_level = bn::string<32>("- ").append(spell_levels[i] > -1 ? "+" : "").append(spell_levels[i]);
            bn::string<32> data_modifier = bn::string<32>("- ").append(data_strings.equipment_def_bad[player.equipment[i].modifierId]);
            bn::string_view data_value;
            switch (player.equipment[i].typeId)
            {
                case equipment_struct::weapon:
                    data_value = data_strings.equipment_weapon[player.equipment[i].equipId];
                    break;
                case equipment_struct::shield:
                    data_value = data_strings.equipment_shield[player.equipment[i].equipId];
                    break;
                case equipment_struct::armour:
                    data_value = data_strings.equipment_armour[player.equipment[i].equipId];
                    break;
            }
            bn::string<32> data = bn::string<32>("- ").append(data_value);
            // equip_list.push_back(data_level);
            equip_list.push_back(data_modifier);
            equip_list.push_back(data);
        }
    }
}


bool game_controller::rome(unsigned int& n, unsigned int dn, bn::string<7>& s, bn::string<7> ds)
{
    if (n >= dn)
    {
        n -= dn;
        s = s + ds;
        return true;
    }
    return false;
}

bn::string<7> game_controller::intToRome(unsigned int n)
{
    bn::string<7> result = "";

    while (rome(n, 10000, result, "T")) {}
    rome(n, 9000, result, "MT");
    rome(n, 5000, result, "A");
    rome(n, 4000, result, "MA");
    while (rome(n, 1000, result, "M")) {}
    rome(n, 900, result, "CM");
    rome(n, 500, result, "D");
    rome(n, 400, result, "CD");
    while (rome(n, 100, result, "C")) {}
    rome(n, 90, result, "XC");
    rome(n, 50, result, "L");
    rome(n, 40, result, "XL");
    while (rome(n, 10, result, "X")) {}
    rome(n, 9, result, "IX");
    rome(n, 5, result, "V");
    rome(n, 4, result, "IV");
    while (rome(n, 1, result, "I")) {}

    return result;
}


void game_controller::drawTab1(player_struct& player, data_strings& data_strings)
{
    active_background->set_item(background_1.value());
    for (int i = 0; i < 4; i++)
    {
        for (auto c : titles[i])
        {
            c.set_top_left_y(i == 0 ? 0 : 2);
        }
    }

    scrollbars.clear();
    scrollbars.push_back(scroll->create_sprite(1));
    scrollbars.push_back(scroll->create_sprite(2));
    scrollbars[0].set_top_left_position(216, 48);
    scrollbars[1].set_top_left_position(216, 90);

    scroll_thumb->set_top_left_position(216, 64);
    scroll_thumb->set_visible(true);

    player_data.clear();
    player_data_labels.clear();
    player_data_default_positions.clear();

    text_generator->set_left_alignment();
    text_generator->generate_top_left(10, 33, "Trait", player_data_labels);
    text_generator->generate_top_left(50, 33, "Value", player_data_labels);

    player_data.push_back(bn::vector<bn::sprite_ptr, 32>());
    player_data_default_positions.push_back(bn::point(9, 47));
    text_generator->generate_top_left(player_data_default_positions[0], "Race", player_data[0]);
    text_generator->generate_top_left(player_data_default_positions[0] + bn::point(0, 16), "Class", player_data[0]);
    text_generator->generate_top_left(player_data_default_positions[0] + bn::point(0, 32), "Level", player_data[0]);
    text_generator->generate_top_left(player_data_default_positions[0] + bn::point(40, 0), data_strings.races[player.race_id], player_data[0]);
    text_generator->generate_top_left(player_data_default_positions[0] + bn::point(40, 16), data_strings.classes[player.class_id], player_data[0]);
    text_generator->generate_top_left(player_data_default_positions[0] + bn::point(40, 32), bn::to_string<5>(player.level), player_data[0]);

    text_generator->generate_top_left(142, 33, "Stat", player_data_labels);
    text_generator->generate_top_left(182, 33, "Value", player_data_labels);

    player_data.push_back(bn::vector<bn::sprite_ptr, 32>());
    player_data_default_positions.push_back(bn::point(141, 47));
    for (int i = scroll_values[highlightedScrollbar]; i < scroll_values[highlightedScrollbar] + 4; i++)
    {
        text_generator->generate_top_left(player_data_default_positions[1] + bn::point(0, (i - scroll_values[highlightedScrollbar]) * 16), data_strings.stats[i], player_data[1]);
        text_generator->generate_top_left(player_data_default_positions[1] + bn::point(40, (i - scroll_values[highlightedScrollbar]) * 16), bn::to_string<5>(player.stats[i]), player_data[1]);
    }

    updateScrollbar(player);
}

void game_controller::drawTab2(player_struct& player, data_strings& data_strings)
{
    active_background->set_item(background_2.value());
    for (int i = 0; i < 4; i++)
    {
        for (auto c : titles[i])
        {
            c.set_top_left_y(i == 1 ? 0 : 2);
        }
    }

    scrollbars.clear();
    scrollbars.push_back(scroll->create_sprite(1));
    scrollbars.push_back(scroll->create_sprite(2));
    scrollbars[0].set_top_left_position(100, 48);
    scrollbars[1].set_top_left_position(100, 112);
    scrollbars.push_back(scroll->create_sprite(1));
    scrollbars.push_back(scroll->create_sprite(2));
    scrollbars[2].set_top_left_position(216, 32);
    scrollbars[3].set_top_left_position(216, 112);

    scroll_thumb->set_top_left_position(100, 64);
    scroll_thumb->set_visible(true);

    player_data.clear();
    player_data_labels.clear();
    player_data_default_positions.clear();

    text_generator->set_left_alignment();
    text_generator->generate_top_left(10, 33, "Spell", player_data_labels);
    text_generator->generate_top_left(80, 33, "Value", player_data_labels);

    player_data.push_back(bn::vector<bn::sprite_ptr, 32>());
    player_data_default_positions.push_back(bn::point(9, 48));
    for (int i = scroll_values[0]; i < scroll_values[0] + 5; i++)
    {
        if (spell_list.size() > i)
        {
            text_generator->generate_top_left(player_data_default_positions[0] + bn::point(0, (i - scroll_values[0]) * 16), spell_list[i], player_data[0]);
            if (spell_levels[i] > 0)
            {
                text_generator->generate_top_left(player_data_default_positions[0] + bn::point(70, (i - scroll_values[0]) * 16), bn::to_string<5>(spell_levels[i]), player_data[0]);
            }
        }
    }

    player_data.push_back(bn::vector<bn::sprite_ptr, 32>());
    player_data_default_positions.push_back(bn::point(125, 32));
    for (int i = scroll_values[1]; i < scroll_values[1] + 6; i++)
    {
        if (equip_list.size() > i)
        {
            text_generator->generate_top_left(player_data_default_positions[1] + bn::point(0, (i - scroll_values[1]) * 16), equip_list[i], player_data[1]);
        }
    }

    updateScrollbar(player);
}

void game_controller::enter(player_struct& player, data_strings& data_strings)
{
    background_1 = bn::regular_bg_items::scr_stats;
    background_2 = bn::regular_bg_items::scr_equip;
    background_3 = bn::regular_bg_items::scr_inv;
    background_4 = bn::regular_bg_items::scr_main;
    active_background = background_1->create_bg(0, 0);
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
    title_strings.push_back("Stats");
    title_strings.push_back("Equipment");
    title_strings.push_back("Inventory");
    title_strings.push_back("Quests");

    player_data_default_positions = bn::vector<bn::point, 2>();
    scroll = bn::sprite_items::spr_scroll;
    scroll_thumb = scroll->create_sprite(0);
    scroll_values = bn::vector<int, 2>();
    scroll_values.push_back(0); // ignored
    scroll_values.push_back(0);

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

    spell_list = bn::vector<bn::string<32>, 61>();
    spell_levels = bn::vector<short, 11>();
    equip_list = bn::vector<bn::string<32>, 33>();

    drawTab1(player, data_strings);
}

void game_controller::update(player_struct& player, data_strings& data_strings)
{
    if (bn::keypad::right_released())
    {
        highlightedScrollbar = 1;
        updateScrollbar(player);
    }
    else if (bn::keypad::left_released())
    {
        highlightedScrollbar = 0;
        updateScrollbar(player);
    }
    else if (bn::keypad::up_pressed())
    {
        decrementHighlightedScrollbar();
        switch (activeTab)
        {
            case 0:
                drawTab1(player, data_strings);
                break;
            case 1:
                drawTab2(player, data_strings);
                break;
        }
    }
    else if (bn::keypad::down_pressed())
    {
        incrementHighlightedScrollbar(player);
        switch (activeTab)
        {
            case 0:
                drawTab1(player, data_strings);
                break;
            case 1:
                drawTab2(player, data_strings);
                break;
        }
    }
    else if (bn::keypad::r_pressed())
    {
        if (incrementActiveTab())
        {
            switch (activeTab)
            {
                case 1:
                    highlightedScrollbar = 0;
                    drawTab2(player, data_strings);
                    break;
                // case 2:
                //     drawTab3(player, data_strings);
                //     break;
                // case 3:
                //     drawTab4(player, data_strings);
                //     break;
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
                    highlightedScrollbar = 1;
                    drawTab1(player, data_strings);
                    break;
                case 1:
                    highlightedScrollbar = 0;
                    drawTab2(player, data_strings);
                    break;
                // case 2:
                //     drawTab3(player, data_strings);
                //     break;
            }
        }
    }
}
//
// void game_controller::exit()
// {
//     game_desktop.reset();
//     game_main.reset();
//     button_new.clear();
//     button_load.clear();
// }