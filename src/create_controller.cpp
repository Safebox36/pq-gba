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
#include "bn_sprite_items_spr_stat.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "font.h"
#include "player_struct.h"
#include "data_strings.h"

bool create_controller::incrementActiveTab()
{
    if (activeTab == 3)
    {
        return false;
    }
    activeTab++;
    highlightedOption.set_position(0, 0);
    highlightedOption.set_dimensions(0, 0);
    return true;
}

bool create_controller::decrementActiveTab()
{
    if (activeTab == 0)
    {
        return false;
    }
    activeTab--;
    highlightedOption.set_position(0, 0);
    highlightedOption.set_dimensions(0, 0);
    return true;
}

bool create_controller::incrementHighlightedOptionX()
{
    switch (activeTab)
    {
        case 0:
        case 2:
            if (highlightedOption.x() == 1)
            {
                return false;
            }
            break;
        case 1:
        case 3:
            if (highlightedOption.x() == 0)
            {
                return false;
            }
            break;
    }
    highlightedOption.set_dimensions(highlightedOption.x(), highlightedOption.y());
    highlightedOption.set_x(highlightedOption.x() + 1);
    return true;
}

bool create_controller::decrementHighlightedOptionX()
{
    if (highlightedOption.x() == 0)
    {
        return false;
    }
    highlightedOption.set_dimensions(highlightedOption.x(), highlightedOption.y());
    highlightedOption.set_x(highlightedOption.x() - 1);
    return true;
}

bool create_controller::incrementHighlightedOptionY()
{
    switch (activeTab)
    {
        case 0:
        case 2:
            if (highlightedOption.y() == 7)
            {
                return false;
            }
            break;
        case 1:
            if (highlightedOption.y() == 4)
            {
                return false;
            }
            break;
        case 3:
            if (highlightedOption.y() == 1)
            {
                return false;
            }
            break;
    }
    highlightedOption.set_dimensions(highlightedOption.x(), highlightedOption.y());
    highlightedOption.set_y(highlightedOption.y() + 1);
    return true;
}

bool create_controller::decrementHighlightedOptionY()
{
    if (highlightedOption.y() == 0)
    {
        return false;
    }
    highlightedOption.set_dimensions(highlightedOption.x(), highlightedOption.y());
    highlightedOption.set_y(highlightedOption.y() - 1);
    return true;
}

void create_controller::updateBullets(player_struct& player, bool refreshAll)
{
    int optionIndex = highlightedOption.x() * 8 + highlightedOption.y();
    int previousOptionIndex = highlightedOption.width() * 8 + highlightedOption.height();
    bool selectedOption;
    bool selectedPreviousOption;
    switch (activeTab)
    {
        case 0:
            selectedOption = player.race_id == optionIndex;
            selectedPreviousOption = player.race_id == previousOptionIndex;
            break;
        case 1:
            selectedOption = player.race_id == (optionIndex + 16);
            selectedPreviousOption = player.race_id == (previousOptionIndex + 16);
            break;
        case 2:
            selectedOption = player.class_id == optionIndex;
            selectedPreviousOption = player.class_id == previousOptionIndex;
            break;
        case 3:
            selectedOption = player.class_id == (optionIndex + 16);
            selectedPreviousOption = player.class_id == (previousOptionIndex + 16);
            break;
    }

    if (refreshAll)
    {
        for (int i = 0; i < bullets.size(); i++)
        {
            if (optionIndex == i)
            {
                bullets[optionIndex].set_item(bullet.value(), selectedOption + 2);
            }
            else
            {
                switch (activeTab)
                {
                    case 0:
                    case 2:
                        bullets[i].set_item(bullet.value(), 0);
                        break;
                    case 1:
                        if (i < 5)
                        {
                            bullets[i].set_item(bullet.value(), 0);
                        }
                        else
                        {
                            bullets[i].set_item(stat.value(), 0);
                        }
                        break;
                    case 3:
                        if (i < 2)
                        {
                            bullets[i].set_item(bullet.value(), 0);
                        }
                        else
                        {
                            bullets[i].set_item(stat.value(), 0);
                        }
                        break;
                }
            }
        }
    }
    else
    {
        bullets[optionIndex].set_item(bullet.value(), selectedOption + 2);
        bullets[previousOptionIndex].set_item(bullet.value(), selectedPreviousOption);
        player.generateNewSeed();
    }
}

void create_controller::updateLabels(player_struct& player, data_strings& data_strings)
{
    if (activeTab == 1)
    {
        bullet_titles.clear();

        text_generator->set_left_alignment();
        for (int i = 0; i < 5; i++)
        {
            text_generator->generate_top_left(bullets[i].top_left_position() + bn::fixed_point(20, 2), data_strings.races[16 + i], bullet_titles);
        }

        for (int i = 0; i < 6; i++)
        {
            text_generator->generate_top_left(120 + 8, 22 + 32 + (i * 16), data_strings.stats[i], bullet_titles);
        }

        text_generator->set_center_alignment();
        text_generator->generate_top_left(120 + 60, 22, "Stats Summary", bullet_titles);
        for (int i = 0; i < 6; i++)
        {
            text_generator->generate_top_left(240 - 8 - 16, 22 + 32 + (i * 16), bn::to_string<2>(player.stats[i]), bullet_titles);
        }

        text_generator->generate_top_left(240 - 8 - 16, 22 + 16, bn::to_string<3>(player.stats[0] + player.stats[1] + player.stats[2] + player.stats[3] + player.stats[4] + player.stats[5]), bullet_titles);

        text_generator->generate_top_left(60, 22 + 32 + (16 * 4), "(B) to re-roll.", bullet_titles);
        text_generator->generate_top_left(60, 22 + 32 + (16 * 5), "(START) when sold.", bullet_titles);
    }
    else if (activeTab == 3)
    {
        bullet_titles.clear();

        text_generator->set_left_alignment();
        for (int i = 0; i < 2; i++)
        {
            text_generator->generate_top_left(bullets[i].top_left_position() + bn::fixed_point(20, 2), data_strings.classes[16 + i], bullet_titles);
        }

        for (int i = 0; i < 6; i++)
        {
            text_generator->generate_top_left(120 + 8, 22 + 32 + (i * 16), data_strings.stats[i], bullet_titles);
        }

        text_generator->set_center_alignment();
        text_generator->generate_top_left(120 + 60, 22, "Stats Summary", bullet_titles);
        for (int i = 0; i < 6; i++)
        {
            text_generator->generate_top_left(240 - 8 - 16, 22 + 32 + (i * 16), bn::to_string<2>(player.stats[i]), bullet_titles);
        }

        text_generator->generate_top_left(240 - 8 - 16, 22 + 16, bn::to_string<3>(player.stats[0] + player.stats[1] + player.stats[2] + player.stats[3] + player.stats[4] + player.stats[5]), bullet_titles);

        text_generator->generate_top_left(60, 22 + 32 + (16 * 4), "(B) to re-roll.", bullet_titles);
        text_generator->generate_top_left(60, 22 + 32 + (16 * 5), "(START) when sold.", bullet_titles);
    }
}


void create_controller::drawTab1(player_struct& player, data_strings& data_strings)
{
    active_background->set_item(background_1.value());
    for (int i = 0; i < 4; i++)
    {
        for (auto c : titles[i])
        {
            c.set_top_left_y(i == 0 ? 0 : 2);
        }
    }

    bullets.clear();
    bullet_titles.clear();

    bool selectedOption;
    text_generator->set_left_alignment();
    for (int i = 0; i < 8; i++)
    {
        selectedOption = player.race_id == i;
        bullets.push_back(bullet->create_sprite(selectedOption + (i == 0 ? 2 : 0)));
        bullets[i].set_top_left_position(8, 20 + (i * 16));
        text_generator->generate_top_left(bullets[i].top_left_position() + bn::fixed_point(20, 2), data_strings.races[i], bullet_titles);
    }
    for (int i = 8; i < 16; i++)
    {
        selectedOption = player.race_id == i;
        bullets.push_back(bullet->create_sprite(selectedOption));
        bullets[i].set_top_left_position(120 + 8, 20 + ((i - 8) * 16));
        text_generator->generate_top_left(bullets[i].top_left_position() + bn::fixed_point(20, 2), data_strings.races[i], bullet_titles);
    }
}

void create_controller::drawTab2(player_struct& player, data_strings& data_strings)
{
    active_background->set_item(background_2.value());
    for (int i = 0; i < 4; i++)
    {
        for (auto c : titles[i])
        {
            c.set_top_left_y(i == 1 ? 0 : 2);
        }
    }

    bullets.clear();
    bullet_titles.clear();

    text_generator->set_left_alignment();
    for (int i = 0; i < 5; i++)
    {
        bool selectedOption = player.race_id == (i + 16);
        bullets.push_back(bullet->create_sprite(selectedOption + (i == 0 ? 2 : 0)));
        bullets[i].set_top_left_position(8, 20 + (i * 16));
        text_generator->generate_top_left(bullets[i].top_left_position() + bn::fixed_point(20, 2), data_strings.races[16 + i], bullet_titles);
    }

    for (int i = 0; i < 6; i++)
    {
        text_generator->generate_top_left(120 + 8, 22 + 32 + (i * 16), data_strings.stats[i], bullet_titles);
    }

    text_generator->set_center_alignment();
    text_generator->generate_top_left(120 + 60, 22, "Stats Summary", bullet_titles);
    for (int i = 0; i < 6; i++)
    {
        bullets.push_back(stat->create_sprite());
        bullets[bullets.size() - 1].set_top_left_position(240 - 8 - 32, 22 + 32 + (i * 16) - 1);
        text_generator->generate_top_left(240 - 8 - 16, 22 + 32 + (i * 16), bn::to_string<2>(player.stats[i]), bullet_titles);
    }

    bullets.push_back(stat->create_sprite());
    bullets[bullets.size() - 1].set_top_left_position(240 - 8 - 32, 22 + 16 - 1);
    text_generator->generate_top_left(240 - 8 - 16, 22 + 16, bn::to_string<3>(player.stats[0] + player.stats[1] + player.stats[2] + player.stats[3] + player.stats[4] + player.stats[5]), bullet_titles);

    text_generator->generate_top_left(60, 22 + 32 + (16 * 4), "(B) to re-roll.", bullet_titles);
    text_generator->generate_top_left(60, 22 + 32 + (16 * 5), "(START) when sold.", bullet_titles);
}

void create_controller::drawTab3(player_struct& player, data_strings& data_strings)
{
    active_background->set_item(background_3.value());
    for (int i = 0; i < 4; i++)
    {
        for (auto c : titles[i])
        {
            c.set_top_left_y(i == 2 ? 0 : 2);
        }
    }

    bullets.clear();
    bullet_titles.clear();

    bool selectedOption;
    text_generator->set_left_alignment();
    for (int i = 0; i < 8; i++)
    {
        selectedOption = player.class_id == i;
        bullets.push_back(bullet->create_sprite(selectedOption + (i == 0 ? 2 : 0)));
        bullets[i].set_top_left_position(8, 20 + (i * 16));
        text_generator->generate_top_left(bullets[i].top_left_position() + bn::fixed_point(20, 2), data_strings.classes[i], bullet_titles);
    }
    for (int i = 8; i < 16; i++)
    {
        selectedOption = player.class_id == i;
        bullets.push_back(bullet->create_sprite(selectedOption));
        bullets[i].set_top_left_position(120 + 8, 20 + ((i - 8) * 16));
        text_generator->generate_top_left(bullets[i].top_left_position() + bn::fixed_point(20, 2), data_strings.classes[i], bullet_titles);
    }
}

void create_controller::drawTab4(player_struct& player, data_strings& data_strings)
{
    active_background->set_item(background_4.value());
    for (int i = 0; i < 4; i++)
    {
        for (auto c : titles[i])
        {
            c.set_top_left_y(i == 1 ? 0 : 2);
        }
    }

    bullets.clear();
    bullet_titles.clear();

    text_generator->set_left_alignment();
    for (int i = 0; i < 2; i++)
    {
        bool selectedOption = player.class_id == (i + 16);
        bullets.push_back(bullet->create_sprite(selectedOption + (i == 0 ? 2 : 0)));
        bullets[i].set_top_left_position(8, 20 + (i * 16));
        text_generator->generate_top_left(bullets[i].top_left_position() + bn::fixed_point(20, 2), data_strings.classes[16 + i], bullet_titles);
    }

    for (int i = 0; i < 6; i++)
    {
        text_generator->generate_top_left(120 + 8, 22 + 32 + (i * 16), data_strings.stats[i], bullet_titles);
    }

    text_generator->set_center_alignment();
    text_generator->generate_top_left(120 + 60, 22, "Stats Summary", bullet_titles);
    for (int i = 0; i < 6; i++)
    {
        bullets.push_back(stat->create_sprite());
        bullets[bullets.size() - 1].set_top_left_position(240 - 8 - 32, 22 + 32 + (i * 16) - 1);
        text_generator->generate_top_left(240 - 8 - 16, 22 + 32 + (i * 16), bn::to_string<2>(player.stats[i]), bullet_titles);
    }

    bullets[bullets.size() - 1].set_top_left_position(240 - 8 - 32, 22 + 16 - 1);
    text_generator->generate_top_left(240 - 8 - 16, 22 + 16, bn::to_string<3>(player.stats[0] + player.stats[1] + player.stats[2] + player.stats[3] + player.stats[4] + player.stats[5]), bullet_titles);

    text_generator->generate_top_left(60, 22 + 32 + (16 * 4), "(B) to re-roll.", bullet_titles);
    text_generator->generate_top_left(60, 22 + 32 + (16 * 5), "(START) when sold.", bullet_titles);
}

void create_controller::enter(player_struct& player, data_strings& data_strings)
{
    background_1 = bn::regular_bg_items::scr_create_1;
    background_2 = bn::regular_bg_items::scr_create_2;
    background_3 = bn::regular_bg_items::scr_create_3;
    background_4 = bn::regular_bg_items::scr_create_4;
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
    title_strings.push_back("Races 1");
    title_strings.push_back("Races 2");
    title_strings.push_back("Classes 1");
    title_strings.push_back("Classes 2");

    bullet = bn::sprite_items::spr_bullet;
    bullet_titles = bn::vector<bn::sprite_ptr, 24>();

    stat = bn::sprite_items::spr_stat;

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

    player.roll();

    drawTab1(player, data_strings);
}

void create_controller::update(int& nextScreen, player_struct& player, data_strings& data_strings)
{
    if (bn::keypad::a_pressed())
    {
        switch (activeTab)
        {
            case 0:
                player.race_id = highlightedOption.x() * 8 + highlightedOption.y();
                updateBullets(player, true);
                break;
            case 1:
                player.race_id = highlightedOption.y() + 16;
                updateBullets(player, true);
                break;
            case 2:
                player.class_id = highlightedOption.x() * 8 + highlightedOption.y();
                updateBullets(player, true);
                break;
            case 3:
                player.class_id = highlightedOption.y() + 16;
                updateBullets(player, true);
                break;
        }
        player.roll();
        updateLabels(player, data_strings);
    }
    else if (bn::keypad::b_pressed())
    {
        player.roll();
        updateLabels(player, data_strings);
    }
    else if (bn::keypad::start_pressed())
    {
        nextScreen = 2;
        exit();
    }
    else if (bn::keypad::right_pressed())
    {
        if (incrementHighlightedOptionX())
        {
            updateBullets(player);
        }
    }
    else if (bn::keypad::left_pressed())
    {
        if (decrementHighlightedOptionX())
        {
            updateBullets(player);
        }
    }
    else if (bn::keypad::up_pressed())
    {
        if (decrementHighlightedOptionY())
        {
            updateBullets(player);
        }
    }
    else if (bn::keypad::down_pressed())
    {
        if (incrementHighlightedOptionY())
        {
            updateBullets(player);
        }
    }
    else if (bn::keypad::r_pressed())
    {
        if (incrementActiveTab())
        {
            switch (activeTab)
            {
                case 1:
                    drawTab2(player, data_strings);
                    break;
                case 2:
                    drawTab3(player, data_strings);
                    break;
                case 3:
                    drawTab4(player, data_strings);
                    break;
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
                    drawTab1(player, data_strings);
                    break;
                case 1:
                    drawTab2(player, data_strings);
                    break;
                case 2:
                    drawTab3(player, data_strings);
                    break;
            }
        }
    }
}

void create_controller::exit()
{
    background_1.reset();
    background_2.reset();
    background_3.reset();
    background_4.reset();
    active_background.reset();
    tabs.reset();
    titles.clear();
    text_generator.reset();
    title_strings.clear();
    bullet.reset();
    bullets.clear();
    bullet_titles.clear();
    stat.reset();
}