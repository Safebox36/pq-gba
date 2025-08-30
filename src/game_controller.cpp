#include "game_controller.h"

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_vector.h"
#include "bn_fixed.h"
#include "bn_log.h"
#include "bn_sram.h"
#include "bn_regular_bg_items_scr_stats.h"
#include "bn_regular_bg_items_scr_equip.h"
#include "bn_regular_bg_items_scr_inv.h"
#include "bn_regular_bg_items_scr_main.h"
#include "bn_sprite_items_spr_scroll.h"
#include "bn_sprite_items_spr_progress.h"
#include "bn_sprite_items_spr_check.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "font.h"
#include "player_struct.h"
#include "data_strings.h"

int game_controller::lerp(bn::fixed v0, bn::fixed v1, bn::fixed t)
{
    return (v0 + t.safe_multiplication(v1 - v0)).round_integer();
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
                if (spell_list.size() == 0 || scroll_values[highlightedScrollbar] >= spell_list.size() - 5)
                {
                    return false;
                }
            }
            else if (highlightedScrollbar == 1)
            {
                if (equip_list.size() == 0 || scroll_values[highlightedScrollbar] >= equip_list.size() - 6)
                {
                    return false;
                }
            }
            break;
        case 2:
            if (scroll_values[highlightedScrollbar] >= player.inventory.size() - 4)
            {
                return false;
            }
            break;
        case 3:
            if (highlightedScrollbar == 0)
            {
                if (scroll_values[highlightedScrollbar] >= player.plot_queue.size() - 5)
                {
                    return false;
                }
            }
            else if (highlightedScrollbar == 1)
            {
                if (scroll_values[highlightedScrollbar] >= player.quest_queue.size() - 5)
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
            if (player.stats.size() - 4 > 0 && scroll_values[highlightedScrollbar] > player.stats.size() - 4) scroll_values[highlightedScrollbar] = player.stats.size() - 4;
            scrollPos = bn::point(scrollbars[0].top_left_position().x().integer(), lerp(scrollbars[0].top_left_position().y() + 16, scrollbars[1].top_left_y() - 16, bn::max<bn::fixed>(0, bn::fixed(scroll_values[highlightedScrollbar]).safe_division(player.stats.size() - 4))));
            break;
        case 1:
            if (highlightedScrollbar == 0)
            {
                if (spell_list.size() - 5 > 0 && scroll_values[highlightedScrollbar] > spell_list.size() - 5) scroll_values[highlightedScrollbar] = spell_list.size() - 5;
                scrollPos = bn::point(scrollbars[0].top_left_position().x().integer(), lerp(scrollbars[0].top_left_position().y() + 16, scrollbars[1].top_left_y() - 16, (spell_list.size() - 5 > 0) ? bn::fixed(scroll_values[highlightedScrollbar]).safe_division(spell_list.size() - 5) : 0));
            }
            else if (highlightedScrollbar == 1)
            {
                if (equip_list.size() - 6 > 0 && scroll_values[highlightedScrollbar] > equip_list.size() - 6) scroll_values[highlightedScrollbar] = equip_list.size() - 6;
                scrollPos = bn::point(scrollbars[2].top_left_position().x().integer(), lerp(scrollbars[2].top_left_position().y() + 16, scrollbars[3].top_left_y() - 16, bn::max<bn::fixed>(0, bn::fixed(scroll_values[highlightedScrollbar]).safe_division(equip_list.size() - 6))));
            }
            break;
        case 2:
            if (player.inventory.size() - 4 > 0 && scroll_values[highlightedScrollbar] > player.inventory.size() - 4) scroll_values[highlightedScrollbar] = player.inventory.size() - 4;
            scrollPos = bn::point(scrollbars[0].top_left_position().x().integer(), lerp(scrollbars[0].top_left_position().y() + 16, scrollbars[1].top_left_y() - 16, (player.inventory.size() - 4 > 0) ? bn::fixed(scroll_values[highlightedScrollbar]).safe_division(player.inventory.size() - 4) : 0));
            break;
        case 3:
            if (highlightedScrollbar == 0)
            {
                if (player.plot_queue.size() - 5 > 0 && scroll_values[highlightedScrollbar] > player.plot_queue.size() - 5) scroll_values[highlightedScrollbar] = player.plot_queue.size() - 5;
                scrollPos = bn::point(scrollbars[0].top_left_position().x().integer(), lerp(scrollbars[0].top_left_position().y() + 16, scrollbars[1].top_left_y() - 16, (player.plot_queue.size() - 5 > 0) ? bn::fixed(scroll_values[highlightedScrollbar]).safe_division(player.plot_queue.size() - 5) : 0));
            }
            else if (highlightedScrollbar == 1)
            {
                if (player.quest_queue.size() - 5 > 0 && scroll_values[highlightedScrollbar] > player.quest_queue.size() - 5) scroll_values[highlightedScrollbar] = player.quest_queue.size() - 5;
                scrollPos = bn::point(scrollbars[2].top_left_position().x().integer(), lerp(scrollbars[2].top_left_position().y() + 16, scrollbars[3].top_left_y() - 16, (player.quest_queue.size() - 5 > 0) ? bn::fixed(scroll_values[highlightedScrollbar]).safe_division(player.quest_queue.size() - 5) : 0));
            }
            break;
    }
    scroll_thumb->set_top_left_position(scrollPos);
}

void game_controller::updateLists(player_struct& player, data_strings& data_strings)
{
    spell_list.clear();
    spell_levels.clear();
    equip_list.clear();
    for (auto spell : player.spells)
    {
        auto data = bn::string_view(data_strings.spells[spell.id]);
        if (data_strings.isSpellMultiline(spell.id))
        {
            auto firstLine = split(data, 0);
            auto secondLine = split(data, 1);
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
            short lvl = player.equipment[i].plusMinus;
            bn::string<32> data = bn::string<32>(", ");
            bn::string<32> data_level = bn::string<32>(", ");
            bn::string<32> data_modifier1 = bn::string<32>(", ");
            bn::string<32> data_modifier2 = bn::string<32>(", ");
            switch (player.equipment[i].baseEquipTypeId)
            {
                case equipment_struct::weapon:
                    data.append(data_strings.equipment_weapon[player.equipment[i].equipId]);
                    if (lvl != 0)
                    {
                        data_level.append(lvl > 0 ? "+" : "").append(bn::to_string<32>(lvl));
                    }
                    break;
                case equipment_struct::shield:
                case equipment_struct::armour:
                    if (player.equipment[i].baseEquipTypeId == equipment_struct::shield)
                    {
                        data.append(data_strings.equipment_shield[player.equipment[i].equipId]);
                    }
                    else
                    {
                        data.append(data_strings.equipment_armour[player.equipment[i].equipId]);
                    }
                    if (lvl != 0)
                    {
                        data_level.append(lvl > 0 ? "+" : "").append(bn::to_string<32>(lvl));
                    }
                    break;
                case equipment_struct::dummy:
                    data.append(i == 0 ? "Sharp Stick" : "(none)");
                    data_modifier1 = "";
                    break;
            }
            if (data_modifier1.length() > 0)
            {
                switch (player.equipment[i].modifierEquipTypeId)
                {
                    case equipment_struct::weapon:
                        if (player.equipment[i].modifierTypeId1 == equipment_struct::bad)
                        {
                            data_modifier1.append(data_strings.equipment_off_bad[player.equipment[i].modifierId1]);
                            if (player.equipment[i].hasModifier2) data_modifier2.append(data_strings.equipment_off_bad[player.equipment[i].modifierId2]);
                        }
                        else
                        {
                            data_modifier1.append(data_strings.equipment_off[player.equipment[i].modifierId1]);
                            if (player.equipment[i].hasModifier2) data_modifier2.append(data_strings.equipment_off[player.equipment[i].modifierId2]);
                        }
                        break;
                    case equipment_struct::shield:
                    case equipment_struct::armour:
                        if (player.equipment[i].modifierTypeId1 == equipment_struct::bad)
                        {
                            data_modifier1.append(data_strings.equipment_def_bad[player.equipment[i].modifierId1]);
                            if (player.equipment[i].hasModifier2) data_modifier2.append(data_strings.equipment_def_bad[player.equipment[i].modifierId2]);
                        }
                        else
                        {
                            data_modifier1.append(data_strings.equipment_def[player.equipment[i].modifierId1]);
                            if (player.equipment[i].hasModifier2) data_modifier2.append(data_strings.equipment_def[player.equipment[i].modifierId2]);
                        }
                        break;
                    case equipment_struct::dummy:
                        break;
                }
                if (lvl != 0)
                {
                    equip_list.push_back(data_level);
                }
                equip_list.push_back(data_modifier1);
                if (player.equipment[i].hasModifier2) equip_list.push_back(data_modifier2);
            }
            equip_list.push_back(data);
        }
    }

    auto invCount = 0;
    for (auto i : player.inventory)
    {
        if (i.typeId == item_struct::gold) continue;
        invCount += i.count;
    }
    player.enc.value = invCount;
}

bn::string<64> game_controller::clipKill(player_struct& player)
{
    int charCount = 0;
    int length = 0;
    for (auto c : player.kill.substr(player.ticker_offset))
    {
        bool done = false;
        for (int i = 0; i < (sizeof(font_regular_chars) / sizeof(font_regular_chars[0])); i++)
        {
            if (c == font_regular_chars[i])
            {
                if (length + font_regular_widths[i] > 232)
                {
                    done = true;
                }
                else
                {
                    charCount++;
                    length += font_regular_widths[i];
                }
                break;
            }
        }
        if (done)
        {
            if (c == ' ')
            {
                charCount--;
            }
            break;
        }
    }
    bn::string<64> outMessage = ((player.ticker_offset + charCount) < player.kill.length() ? player.kill.substr(player.ticker_offset, player.ticker_offset + charCount - 3) : player.kill);
    if (outMessage.back() == ' ') outMessage.pop_back();
    outMessage.append("...");
    // if ((player.ticker_offset + charCount) < player.kill.length() + 3)
    // {
    //     player.ticker_offset++;
    // }
    // else
    // {
    //     player.ticker_offset = 0;
    // }
    return outMessage;
}

bn::string<64> game_controller::clipQuest(bn::string<128>& quest)
{
    int charCount = 0;
    int length = 0;
    for (auto c : quest)
    {
        bool done = false;
        for (int i = 0; i < (sizeof(font_regular_chars) / sizeof(font_regular_chars[0])); i++)
        {
            if (c == font_regular_chars[i])
            {
                if (length + font_regular_widths[i] > 101)
                {
                    done = true;
                }
                else
                {
                    charCount++;
                    length += font_regular_widths[i];
                }
                break;
            }
        }
        if (done)
        {
            if (c == ' ')
            {
                charCount--;
            }
            break;
        }
    }
    bn::string<64> outMessage = charCount < quest.length() ? quest.substr(0, charCount - 3) : quest;
    if (outMessage.back() == ' ') outMessage.pop_back();
    if (charCount < quest.length()) outMessage.append("...");
    return outMessage;
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

bn::string<64> game_controller::buildItemName(const item_struct& item, data_strings& data_strings)
{
    bn::string<64> item_name;
    switch (item.typeId)
    {
        case item_struct::gold:
        {
            item_name = bn::string<64>("Gold");
            break;
        }
        case item_struct::monster:
        {
            bn::string<128> monster = data_strings.items_monster[item.id];
            item_name = split(monster, 0).append(" ").append(split(monster, 1));
            item_name = toLower(item_name).substr(0, 64 - 3);
            break;
        }
        case item_struct::boring:
        {
            bn::string<128> boring = data_strings.items_boring[item.id];
            item_name = boring.substr(0, 64 - 3);
            item_name = toLower(item_name);
            break;
        }
        case item_struct::interesting:
        {
            bn::string<128> interesting = bn::string<128>(data_strings.item_modifiers[item.modifierId]).append(" ").append(data_strings.item_specials[item.id]);
            item_name = interesting.substr(0, 64 - 3);
            item_name = toLower(item_name);
            break;
        }
        case item_struct::special:
        {
            bn::string<128> special = bn::string<128>(data_strings.item_modifiers[item.modifierId]).append(" ").append(data_strings.item_specials[item.id]).append(" of ").append(data_strings.item_of[item.ofId]);
            item_name = special.substr(0, 64 - 3);
            item_name = toLower(item_name);
            break;
        }
    }
    return item_name;
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
    scrollbars[0].set_top_left_position(216, 32);
    scrollbars[1].set_top_left_position(216, 92);

    player_data.clear();
    player_data_labels.clear();
    player_progress.clear();
    player_data_default_positions.clear();
    task_prog_bar.clear();
    sub_prog_bars.clear();

    bold_text_generator->generate_top_left(7, 16, "Character", player_data_labels);
    bold_text_generator->generate_top_left(139, 16, "Stats", player_data_labels);

    text_generator->set_left_alignment();
    text_generator->generate_top_left(10, 32, "Trait", player_data_labels);
    text_generator->generate_top_left(50, 32, "Value", player_data_labels);

    player_data.push_back(bn::vector<bn::sprite_ptr, 32>());
    player_data_default_positions.push_back(bn::point(9, 48));
    text_generator->generate_top_left(player_data_default_positions[0], "Race", player_data[0]);
    text_generator->generate_top_left(player_data_default_positions[0] + bn::point(0, 16), "Class", player_data[0]);
    text_generator->generate_top_left(player_data_default_positions[0] + bn::point(0, 32), "Level", player_data[0]);
    text_generator->generate_top_left(player_data_default_positions[0] + bn::point(40, 0), data_strings.races[player.race_id], player_data[0]);
    text_generator->generate_top_left(player_data_default_positions[0] + bn::point(40, 16), data_strings.classes[player.class_id], player_data[0]);
    text_generator->generate_top_left(player_data_default_positions[0] + bn::point(40, 32), bn::to_string<5>(player.level), player_data[0]);

    text_generator->generate_top_left(142, 32, "Stat", player_data_labels);
    text_generator->generate_top_left(182, 32, "Value", player_data_labels);

    player_data.push_back(bn::vector<bn::sprite_ptr, 32>());
    player_data_default_positions.push_back(bn::point(141, 48));
    for (int i = scroll_values[highlightedScrollbar]; i < scroll_values[highlightedScrollbar] + 4; i++)
    {
        text_generator->generate_top_left(player_data_default_positions[1] + bn::point(0, (i - scroll_values[highlightedScrollbar]) * 16), data_strings.stats[i], player_data[1]);
        text_generator->generate_top_left(player_data_default_positions[1] + bn::point(40, (i - scroll_values[highlightedScrollbar]) * 16), bn::to_string<5>(player.stats[i]), player_data[1]);
    }

    text_generator->generate_top_left(7, 111, "Experience", player_data_labels);
    text_generator->generate_top_left(4, 138, clipKill(player), player_progress);

    auto maxProg = player.task_prog.numberOfSprites(234);
    for (int i = 0; i < maxProg; i++)
    {
        task_prog_bar.push_back(bn::sprite_items::spr_progress.create_sprite(maxProg - i - 1 == 0 ? player.task_prog.spriteIndex(234) : 0));
        task_prog_bar.back().set_top_left_position(3 + (i * 8), 155);
    }
    auto maxExp = player.exp.numberOfSprites(226);
    for (int i = 0; i < maxExp; i++)
    {
        sub_prog_bars.push_back(bn::sprite_items::spr_progress.create_sprite(maxExp - i - 1 == 0 ? player.exp.spriteIndex(226) : 0));
        sub_prog_bars.back().set_top_left_position(7 + (i * 8), 127);
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
    scrollbars[0].set_top_left_position(100, 32);
    scrollbars[1].set_top_left_position(100, 112);
    scrollbars.push_back(scroll->create_sprite(1));
    scrollbars.push_back(scroll->create_sprite(2));
    scrollbars[2].set_top_left_position(216, 32);
    scrollbars[3].set_top_left_position(216, 112);

    player_data.clear();
    player_data_labels.clear();
    player_progress.clear();
    player_data_default_positions.clear();
    task_prog_bar.clear();
    sub_prog_bars.clear();

    bold_text_generator->generate_top_left(7, 16, "Spells", player_data_labels);
    bold_text_generator->generate_top_left(123, 16, "Equipment", player_data_labels);

    text_generator->set_left_alignment();
    text_generator->generate_top_left(10, 32, "Spell", player_data_labels);
    text_generator->generate_top_left(80, 32, "Lvl", player_data_labels);

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
    player_data_default_positions.push_back(bn::point(125, 34));
    for (int i = scroll_values[1]; i < scroll_values[1] + 6; i++)
    {
        if (equip_list.size() > i)
        {
            text_generator->generate_top_left(player_data_default_positions[1] + bn::point(0, (i - scroll_values[1]) * 16), equip_list[i], player_data[1]);
        }
    }

    text_generator->generate_top_left(4, 138, clipKill(player), player_progress);

    auto maxProg = player.task_prog.numberOfSprites(234);
    for (int i = 0; i < maxProg; i++)
    {
        task_prog_bar.push_back(bn::sprite_items::spr_progress.create_sprite(maxProg - i - 1 == 0 ? player.task_prog.spriteIndex(234) : 0));
        task_prog_bar.back().set_top_left_position(3 + (i * 8), 155);
    }

    updateScrollbar(player);
}

void game_controller::drawTab3(player_struct& player, data_strings& data_strings)
{
    active_background->set_item(background_3.value());
    for (int i = 0; i < 4; i++)
    {
        for (auto c : titles[i])
        {
            c.set_top_left_y(i == 2 ? 0 : 2);
        }
    }

    scrollbars.clear();
    scrollbars.push_back(scroll->create_sprite(1));
    scrollbars.push_back(scroll->create_sprite(2));
    scrollbars[0].set_top_left_position(216, 32);
    scrollbars[1].set_top_left_position(216, 92);

    player_data.clear();
    player_data_labels.clear();
    player_progress.clear();
    player_data_default_positions.clear();
    task_prog_bar.clear();
    sub_prog_bars.clear();

    bold_text_generator->generate_top_left(7, 16, "Inventory", player_data_labels);

    text_generator->set_right_alignment();
    text_generator->generate_top_left(214, 32, "Qty", player_data_labels);
    text_generator->set_left_alignment();
    text_generator->generate_top_left(10, 32, "Item", player_data_labels);

    player_data.push_back(bn::vector<bn::sprite_ptr, 32>());
    player_data.push_back(bn::vector<bn::sprite_ptr, 32>());
    player_data_default_positions.push_back(bn::point(9, 47));
    player_data_default_positions.push_back(bn::point(215, 47));
    for (int i = scroll_values[highlightedScrollbar]; i < scroll_values[highlightedScrollbar] + 4; i++)
    {
        if (player.inventory.size() > i)
        {
            bn::string<64> item = buildItemName(player.inventory[i], data_strings);
            text_generator->generate_top_left(player_data_default_positions[0] + bn::point(0, (i - scroll_values[highlightedScrollbar]) * 16), item.length() == 32 - 3 ? item.append("...") : item, player_data[0]);
            text_generator->set_right_alignment();
            text_generator->generate_top_left(player_data_default_positions[1] + bn::point(0, (i - scroll_values[highlightedScrollbar]) * 16), bn::to_string<5>(player.inventory[i].count), player_data[1]);
            text_generator->set_left_alignment();
        }
    }

    text_generator->generate_top_left(7, 111, "Encumbrance", player_data_labels);
    text_generator->generate_top_left(4, 138, clipKill(player), player_progress);

    auto maxProg = player.task_prog.numberOfSprites(234);
    for (int i = 0; i < maxProg; i++)
    {
        task_prog_bar.push_back(bn::sprite_items::spr_progress.create_sprite(maxProg - i - 1 == 0 ? player.task_prog.spriteIndex(234) : 0));
        task_prog_bar.back().set_top_left_position(3 + (i * 8), 155);
    }
    auto maxEnc = player.enc.numberOfSprites(226);
    for (int i = 0; i < maxEnc; i++)
    {
        sub_prog_bars.push_back(bn::sprite_items::spr_progress.create_sprite(maxEnc - i - 1 == 0 ? player.enc.spriteIndex(226) : 0));
        sub_prog_bars.back().set_top_left_position(7 + (i * 8), 127);
    }

    updateScrollbar(player);
}

void game_controller::drawTab4(player_struct& player, data_strings& data_strings)
{
    active_background->set_item(background_4.value());
    for (int i = 0; i < 4; i++)
    {
        for (auto c : titles[i])
        {
            c.set_top_left_y(i == 3 ? 0 : 2);
        }
    }

    scrollbars.clear();
    scrollbars.push_back(scroll->create_sprite(1));
    scrollbars.push_back(scroll->create_sprite(2));
    scrollbars.push_back(scroll->create_sprite(1));
    scrollbars.push_back(scroll->create_sprite(2));
    scrollbars[0].set_top_left_position(74, 32);
    scrollbars[1].set_top_left_position(74, 106);
    scrollbars[2].set_top_left_position(216, 32);
    scrollbars[3].set_top_left_position(216, 106);

    player_data.clear();
    player_data_labels.clear();
    player_progress.clear();
    player_data_default_positions.clear();
    task_prog_bar.clear();
    sub_prog_bars.clear();

    bold_text_generator->generate_top_left(7, 16, "Plot", player_data_labels);
    bold_text_generator->generate_top_left(97, 16, "Quests", player_data_labels);
    text_generator->set_left_alignment();

    player_data.push_back(bn::vector<bn::sprite_ptr, 32>());
    player_data.push_back(bn::vector<bn::sprite_ptr, 32>());
    player_data_default_positions.push_back(bn::point(23, 33));
    for (int i = scroll_values[0]; i < scroll_values[0] + 5; i++)
    {
        if (player.plot_queue.size() > i)
        {
            player_data[0].push_back(bn::sprite_items::spr_check.create_sprite(player.plot_queue[i].complete ? 1 : 0));
            player_data[0].back().set_top_left_position(player_data_default_positions[0] + bn::point(-16, -1 + (i - scroll_values[0]) * 16));
            text_generator->generate_top_left(player_data_default_positions[0] + bn::point(0, (i - scroll_values[0]) * 16), player.plot_queue[i].desc, player_data[0]);
        }
    }
    player_data_default_positions.push_back(bn::point(113, 33));
    for (int i = scroll_values[1]; i < scroll_values[1] + 5; i++)
    {
        if (player.quest_queue.size() > i)
        {
            player_data[1].push_back(bn::sprite_items::spr_check.create_sprite(player.quest_queue[i].complete ? 1 : 0));
            player_data[1].back().set_top_left_position(player_data_default_positions[1] + bn::point(-16, -1 + (i - scroll_values[1]) * 16));
            text_generator->generate_top_left(player_data_default_positions[1] + bn::point(0, (i - scroll_values[1]) * 16), clipQuest(player.quest_queue[i].desc), player_data[1]);
        }
    }

    text_generator->generate_top_left(4, 138, clipKill(player), player_progress);

    auto maxProg = player.task_prog.numberOfSprites(234);
    for (int i = 0; i < maxProg; i++)
    {
        task_prog_bar.push_back(bn::sprite_items::spr_progress.create_sprite(maxProg - i - 1 == 0 ? player.task_prog.spriteIndex(234) : 0));
        task_prog_bar.back().set_top_left_position(3 + (i * 8), 155);
    }
    auto maxPlot = player.plot_prog.numberOfSprites(85);
    for (int i = 0; i < maxPlot; i++)
    {
        sub_prog_bars.push_back(bn::sprite_items::spr_progress.create_sprite(maxPlot - i - 1 == 0 ? player.plot_prog.spriteIndex(85) : 0));
        sub_prog_bars.back().set_top_left_position(7 + (i * 8), 127);
    }
    auto maxQuest = player.quest_prog.numberOfSprites(137);
    for (int i = 0; i < maxQuest; i++)
    {
        sub_prog_bars.push_back(bn::sprite_items::spr_progress.create_sprite(maxQuest - i - 1 == 0 ? player.quest_prog.spriteIndex(137) : 0));
        sub_prog_bars.back().set_top_left_position(96 + (i * 8), 127);
    }

    updateScrollbar(player);
}

void game_controller::enter(player_struct& player, data_strings& data_strings)
{
    start(player, data_strings);

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
    scroll_values.push_back(0); // ignored for the first tab
    scroll_values.push_back(0);

    text_generator = bn::sprite_text_generator(font_regular);
    bold_text_generator = bn::sprite_text_generator(font_bold);
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
    spell_levels = bn::vector<short, 45>();
    equip_list = bn::vector<bn::string<32>, 33>();
    task_prog_bar = bn::vector<bn::sprite_ptr, 30>();
    sub_prog_bars = bn::vector<bn::sprite_ptr, 29>();

    drawTab1(player, data_strings);
}

void game_controller::update(player_struct& player, data_strings& data_strings)
{
    tick(player, data_strings);

    if (bn::keypad::right_pressed())
    {
        switch (activeTab)
        {
            case 1:
            case 3:
                highlightedScrollbar = 1;
                updateScrollbar(player);
                break;
        }
    }
    else if (bn::keypad::left_pressed())
    {
        switch (activeTab)
        {
            case 1:
            case 3:
                highlightedScrollbar = 0;
                updateScrollbar(player);
                break;
        }
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
            case 2:
                drawTab3(player, data_strings);
                break;
            case 3:
                drawTab4(player, data_strings);
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
            case 2:
                drawTab3(player, data_strings);
                break;
            case 3:
                drawTab4(player, data_strings);
                break;
        }
    }
    else if (bn::keypad::r_pressed())
    {
        if (incrementActiveTab())
        {
            for (auto& v : scroll_values)
            {
                v = 0;
            }
            switch (activeTab)
            {
                case 1:
                    highlightedScrollbar = 0;
                    drawTab2(player, data_strings);
                    break;
                case 2:
                    highlightedScrollbar = 1;
                    drawTab3(player, data_strings);
                    break;
                case 3:
                    highlightedScrollbar = 0;
                    drawTab4(player, data_strings);
                    break;
            }
        }
    }
    else if (bn::keypad::l_pressed())
    {
        if (decrementActiveTab())
        {
            for (auto& v : scroll_values)
            {
                v = 0;
            }
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
                case 2:
                    highlightedScrollbar = 1;
                    drawTab3(player, data_strings);
                    break;
                case 3:
                    highlightedScrollbar = 0;
                    drawTab4(player, data_strings);
                    break;
            }
        }
    }
}

unsigned short game_controller::levelUpTime(unsigned short level)
{
    // Original documentation:
    // ~20 minutes for level 1, eventually dominated by exponential
    bn::fixed powered;
    for (int i = 0; i < level; i++)
    {
        powered = powered.safe_multiplication(1.15f);
    }
    return static_cast<unsigned short>((20.f + powered).safe_multiplication(60.f).round_integer());
}

void game_controller::levelUp(player_struct& player, data_strings& data_strings)
{
    player.level++;
    for (int i = 0; i < 2; i++)
    {
        player.stats[6 + i] = (bn::fixed(player.stats[2 + i] / 3.f) + 1 + player.rng.get_unbiased_int(3)).round_integer();
    }
    for (int i = 0; i < 2; i++)
    {
        winStat(player, data_strings);
    }
    winSpell(player, data_strings);
    player.exp.value = 0;
    player.exp.max = levelUpTime(player.level);
    saveGame(player);
}

void game_controller::task(bn::string<128> message, unsigned short duration, player_struct& player)
{
    player.kill = message;
    player.task_prog.value = 0;
    player.task_prog.max = duration * 60;
}

void game_controller::q(progress_struct data, player_struct& player, data_strings& data_strings)
{
    player.message_queue.push_back(data);
    dequeueQ(player, data_strings);
}

void game_controller::dequeueQ(player_struct& player, data_strings& data_strings)
{
    while (player.task_prog.value >= player.task_prog.max)
    {
        if (split(player.task_data.caption, 0) == "kill")
        {
            if (split(player.task_data.caption, 2) == "*")
            {
                winItem(player, data_strings);
            }
            else if (split(player.task_data.caption, 2) != "")
            {
                bool hasItem = false;
                for (auto& i : player.inventory)
                {
                    if (i.id == player.task_data.reward.value().id && i.typeId == player.task_data.reward.value().typeId && i.ofId == player.task_data.reward.value().ofId)
                    {
                        i.count++;
                        hasItem = true;
                    }
                }
                if (hasItem == false)
                {
                    player.inventory.push_back(player.task_data.reward.value());
                }
            }
        }
        else if (player.task_data.caption == "buying")
        {
            player.inventory[0].count -= equipPrice(player);
            winEquip(player, data_strings);
        }
        else if (player.task_data.caption == "market" || player.task_data.caption == "sell")
        {
            if (player.task_data.caption == "sell")
            {
                auto value = player.inventory[player.inventory.size() - 1].count * player.level;
                if (player.inventory[player.inventory.size() - 1].typeId == item_struct::special)
                {
                    value *= (1 + player.rng.get_unbiased_int(10)) * (1 + player.rng.get_unbiased_int(player.level));
                }
                player.inventory.pop_back();
                player.inventory[0].count += value;
            }
            if (player.inventory.size() > 1)
            {
                auto item = player.inventory[player.inventory.size() - 1];
                bn::string<64> item_name = buildItemName(item, data_strings);
                task(bn::string<128>("Selling ").append(indefinite(item_name, player.inventory[player.inventory.size() - 1].count)), 1, player);
                player.task_data.caption = "sell";
                break;
            }
        }
        bn::string<128> old = player.task_data.caption;
        player.task_data.caption = "";
        if (player.message_queue.size() > 0)
        {
            auto a = player.message_queue.front().typeId;
            auto n = player.message_queue.front().duration;
            auto s = player.message_queue.front().message;
            if (a == progress_struct::task || a == progress_struct::plot)
            {
                if (a == progress_struct::plot)
                {
                    completeAct(player, data_strings);
                    s = "Loading " + player.plot_queue.back().desc;
                }
                task(s, n, player);
                player.message_queue.pop_front();
            }
            else
            {
                BN_LOG("bah!");
            }
        }
        else if (player.enc.value >= player.enc.max)
        {
            task("Heading to market to sell loot", 4, player);
            player.task_data.caption = "market";
        }
        else if (old.find("kill|") <= 0 && (old != "heading"))
        {
            if (player.inventory[0].count > equipPrice(player))
            {
                task("Negotiating purchase of better equipment", 5, player);
                player.task_data.caption = "buying";
            }
            else
            {
                task("Heading to the killing fields", 4, player);
                player.task_data.caption = "heading";
            }
        }
        else
        {
            auto n = player.level;
            auto l = n;
            auto s = monsterTask(n, player, data_strings);
            task("Executing " + s, bn::fixed(6).safe_multiplication(n).safe_division(l).round_integer(), player);
        }
    }
}

void game_controller::completeAct(player_struct& player, data_strings& data_strings)
{
    player.plot_prog.value = 0;
    player.plot_queue.back().complete = true;
    player.plot_prog.max = 60 * 60 * (1 + 5 * player.plot_queue.size()); // 1 hr + 5/act
    player.plot_count++;
    player.plot_queue.push_back(quest_struct(bn::string<128>("Act ").append(bn::to_string<128>(player.plot_count))));
    if (player.plot_queue.size() > 2) winItem(player, data_strings);
    if (player.plot_queue.size() > 3) winEquip(player, data_strings);
    saveGame(player);
}

void game_controller::completeQuest(player_struct& player, data_strings& data_strings)
{
    player.quest_prog.value = 0;
    player.quest_prog.max = 50 + player.rng.get_unbiased_int(100);

    if (player.quest_queue.size() > 0)
    {
        player.quest_queue.back().complete = true;
        switch (player.rng.get_unbiased_int(4))
        {
            case 0:
                winSpell(player, data_strings);
                break;
            case 1:
                winEquip(player, data_strings);
                break;
            case 2:
                winStat(player, data_strings);
                break;
            case 3:
                winItem(player, data_strings);
                break;
        }
    }
    while (player.quest_queue.full())
    {
        player.quest_queue.pop_front();
    }

    switch (player.rng.get_unbiased_int(5))
    {
        case 0:
        {
            bn::string<128> m;
            int lev = 0;
            for (int i = 1; i < 5; i++)
            {
                auto montag = player.rng.get_unbiased_int(data_strings.items_monster.size());
                m = data_strings.items_monster[montag];
                auto l = data_strings.items_monster_val[montag];
                if (i == 1 || (bn::abs(l - player.level) < bn::abs(lev - player.level)))
                {
                    lev = l;
                    player.quest_data.caption = split(m, 0);
                    player.quest_data.tag = montag;
                }
            }
            player.quest_queue.push_back(quest_struct(bn::string<128>("Exterminate ").append(definite(split(player.quest_data.caption, 0), 2))));
            break;
        }
        case 1:
        {
            auto item = interestingItem(player, data_strings);
            bn::string<128> s = data_strings.item_specials[item.id];
            player.quest_queue.push_back(quest_struct(bn::string<128>("Seek ").append(data_strings.item_modifiers[item.modifierId]).append(" ").append(definite(split(s, 1), 1))));
            player.quest_data.caption = "";
            break;
        }
        case 2:
        {
            auto item = boringItem(player, data_strings);
            player.quest_queue.push_back(quest_struct(bn::string<128>("Deliver this ").append(data_strings.items_boring[item.id])));
            player.quest_data.caption = "";
            break;
        }
        case 3:
        {
            auto item = boringItem(player, data_strings);
            player.quest_queue.push_back(quest_struct(bn::string<128>("Fetch me ").append(indefinite(data_strings.items_boring[item.id], 1))));
            player.quest_data.caption = "";
            break;
        }
        case 4:
        {
            int lev = 0;
            for (int i = 1; i < 3; i++)
            {
                auto montag = player.rng.get_unbiased_int(data_strings.items_monster.size());
                auto m = data_strings.items_monster[montag];
                auto l = data_strings.items_monster_val[montag];
                if (i == 1 || (bn::abs(l - player.level) < bn::abs(lev - player.level)))
                {
                    lev = l;
                    player.quest_data.caption = m;
                }
            }
            player.quest_queue.push_back(quest_struct(bn::string<128>("Placate ").append(definite(split(player.quest_data.caption, 0), 2))));
            player.quest_data.caption = "";
            break;
        }
    }
    player.quest_queue.back().complete = false;
    saveGame(player);
}

bn::string<128> game_controller::monsterTask(unsigned short& monster_level, player_struct& player, data_strings& data_strings)
{
    bool definite = false;
    tq_struct monster = tq_struct("", 0);
    unsigned short lev = 0;
    unsigned short count = 0;
    for (int i = monster_level; i > 0; i--)
    {
        if (player.rng.get_unbiased_int(5) < 2)
        {
            monster_level += player.rng.get_unbiased_int(2) * 2 - 1;
        }
    }
    if (monster_level < 1)
    {
        monster_level = 1;
    }
    // Original documentation:
    // level = level of puissance of opponent(s) we'll return

    if (player.rng.get_unbiased_int(25) < 1)
    {
        // Original documentation:
        // use an NPC every once in a while
        monster.caption = bn::string<128>(" ").append(data_strings.races[player.rng.get_unbiased_int(data_strings.races.size())]);
        if (player.rng.get_unbiased_int(2) < 1)
        {
            monster.caption = bn::string<128>("passing").append(monster.caption).append(" ").append(data_strings.classes[player.rng.get_unbiased_int(data_strings.classes.size())]);
        }
        else
        {
            monster.caption = bn::string<128>(data_strings.titles[player.rng.get_unbiased_int(data_strings.titles.size())]).append(" " + generateName(player) + " the").append(monster.caption);
            definite = true;
        }
        lev = monster_level;
        monster.caption = monster.caption.append("|*");
        monster.reward.reset();
    }
    else if (player.quest_data.caption != "" && player.rng.get_unbiased_int(4) < 1)
    {
        // Original documentation:
        // use the quest monster
        monster.caption = data_strings.items_monster[player.quest_data.tag];
        lev = data_strings.items_monster_val[monster.tag];
        monster.reward = item_struct(player.quest_data.tag, item_struct::monster, 0, 0, lev);
    }
    else
    {
        // Original documentation:
        // pick the monster out of so many random ones closest to the level we want
        auto t = player.rng.get_unbiased_int(data_strings.items_monster.size());
        monster.caption = data_strings.items_monster[t];
        monster.tag = data_strings.items_monster_val[t];
        monster.reward = item_struct(t, item_struct::monster, 0, 0, lev);
        lev = monster.tag;
        auto i = 5;
        while (i > 0)
        {
            auto m1 = player.rng.get_unbiased_int(data_strings.items_monster.size());
            if (bn::abs(monster_level - data_strings.items_monster_val[m1]) < bn::abs(monster_level - lev))
            {
                monster.caption = data_strings.items_monster[m1];
                monster.tag = data_strings.items_monster_val[m1];
                monster.reward = item_struct(m1, item_struct::monster, 0, 0, lev);
                lev = m1;
            }
            if (i > 0)
            {
                i--;
            }
        }
    }

    player.task_data = monster;
    bn::string<128> out = split(monster.caption, 0);
    player.task_data.caption = bn::string<128>("kill|").append(player.task_data.caption);

    count = 1;
    if ((monster_level - lev) > 10)
    {
        // Original documentation:
        // lev is too low. multiply...
        count = (monster_level + player.rng.get_unbiased_int(lev)) / bn::max<unsigned short>(lev, 1);
        if (count < 1)
        {
            count = 1;
        }
        monster_level /= count;
    }

    if ((monster_level - lev) <= -10)
    {
        out = bn::string<128>("imaginary ").append(out);
    }
    else if ((monster_level - lev) < -5)
    {
        auto i = 10 + (monster_level - lev);
        i = 5 - player.rng.get_unbiased_int(i + 1);
        out = sick(i, young((lev - monster_level) - i, out));
    }
    else if ((monster_level - lev) < 0 and player.rng.get_unbiased_int(2) == 1)
    {
        out = sick(monster_level - lev, out);
    }
    else if ((monster_level - lev) < 0)
    {
        out = young(monster_level - lev, out);
    }
    else if ((monster_level - lev) >= 10)
    {
        out = bn::string<128>("messianic ").append(out);
    }
    else if ((monster_level - lev) > 5)
    {
        auto i = 10 - (monster_level - lev);
        i = 5 - player.rng.get_unbiased_int(i + 1);
        out = big(i, special((lev - monster_level) - i, out));
    }
    else if ((monster_level - lev) > 0 and player.rng.get_unbiased_int(2) == 1)
    {
        out = big(monster_level - lev, out);
    }
    else if ((monster_level - lev) > 0)
    {
        out = special(monster_level - lev, out);
    }

    lev = monster_level;
    monster_level = lev * count;

    if (!definite)
    {
        out = indefinite(out, count);
    }

    return out;
}

bn::string<128> game_controller::split(bn::string<128> s, int field, char seperator)
{
    int p = 0;
    while (field > 0)
    {
        p = s.find(seperator) ? s.find(seperator) : -1;
        s = s.substr(p + 1);
        field--;
    }
    if (s.find(seperator) > 0)
    {
        return s.substr(0, s.find(seperator));
    }
    else
    {
        return s;
    }
}

bn::string<128> game_controller::split(bn::string<128> s, int field)
{
    return split(s, field, '|');
}

bn::string<64> game_controller::toLower(bn::string<64>& s)
{
    // Stolen from StackOverflow
    const unsigned int diff = 'a' - 'A';

    bn::string<64> lower = "";

    for (int i = 0; i < s.size(); i++)
    {
        lower += (s[i] >= 'A' && s[i] <= 'Z') ? s[i] + diff : s[i];
    }

    return lower;
}

bn::string<128> game_controller::toProper(bn::string<128>& s)
{
    const unsigned int diff = 'a' - 'A';
    bn::string<128> proper = "";
    proper += ((s[0] >= 'a' && s[0] <= 'z') ? s[0] - diff : s[0]);
    return proper.append(s.substr(1));
}

bn::string<128> game_controller::indefinite(const bn::string<128>& s, unsigned short count)
{
    if (count == 1)
    {
        if (s.starts_with("A") || s.starts_with("E") || s.starts_with("I") ||
            s.starts_with("O") || s.starts_with("U") ||
            s.starts_with("a") || s.starts_with("e") || s.starts_with("i") ||
            s.starts_with("o") || s.starts_with("u"))
        {
            return "an " + s;
        }
        else
        {
            return "a " + s;
        }
    }
    else
    {
        return bn::to_string<128>(count) + " " + plural(s);
    }
}

bn::string<128> game_controller::definite(const bn::string<128>& s, unsigned short count)
{
    if (count > 1)
    {
        return "the " + bn::to_string<128>(count) + " " + plural(s);
    }
    else
    {
        return "the " + s;
    }
}

bn::string<128> game_controller::plural(const bn::string<128>& s)
{
    if (s.ends_with('y'))
    {
        return s.substr(1, s.length() - 1) + "ies";
    }
    else if (s.ends_with("us"))
    {
        return s.substr(1, s.length() - 2) + 'i';
    }
    else if (s.ends_with("ch") or s.ends_with('x') or s.ends_with('s'))
    {
        return s + "es";
    }
    else if (s.ends_with('f'))
    {
        return s.substr(1, s.length() - 1) + "ves";
    }
    else if (s.ends_with("man") or s.ends_with("Man"))
    {
        return s.substr(1, s.length() - 2) + "en";
    }
    else
    {
        return s + 's';
    }
}

bn::string<128> game_controller::generateName(player_struct& player)
{
    bn::vector<bn::vector<bn::string<2>, 22>, 3> parts;
    parts.push_back(bn::vector<bn::string<2>, 22>());
    parts.push_back(bn::vector<bn::string<2>, 22>());
    parts.push_back(bn::vector<bn::string<2>, 22>());

    parts[0].push_back("br");
    parts[0].push_back("cr");
    parts[0].push_back("dr");
    parts[0].push_back("fr");
    parts[0].push_back("gr");
    parts[0].push_back("j");
    parts[0].push_back("kr");
    parts[0].push_back("l");
    parts[0].push_back("m");
    parts[0].push_back("n");
    parts[0].push_back("pr");
    parts[0].push_back("");
    parts[0].push_back("");
    parts[0].push_back("");
    parts[0].push_back("r");
    parts[0].push_back("sh");
    parts[0].push_back("tr");
    parts[0].push_back("v");
    parts[0].push_back("wh");
    parts[0].push_back("x");
    parts[0].push_back("y");
    parts[0].push_back("z");
    parts[1].push_back("a");
    parts[1].push_back("a");
    parts[1].push_back("e");
    parts[1].push_back("e");
    parts[1].push_back("i");
    parts[1].push_back("i");
    parts[1].push_back("o");
    parts[1].push_back("o");
    parts[1].push_back("u");
    parts[1].push_back("u");
    parts[1].push_back("ae");
    parts[1].push_back("ie");
    parts[1].push_back("oo");
    parts[1].push_back("ou");
    parts[2].push_back("b");
    parts[2].push_back("ck");
    parts[2].push_back("d");
    parts[2].push_back("g");
    parts[2].push_back("k");
    parts[2].push_back("m");
    parts[2].push_back("n");
    parts[2].push_back("p");
    parts[2].push_back("t");
    parts[2].push_back("v");
    parts[2].push_back("x");
    parts[2].push_back("z");

    bn::string<128> s = "";
    for (int i = 0; i < 6; i++)
    {
        auto k = parts[i % 3];
        s = s.append(k[player.rng.get_unbiased_int(k.size())]);
    }
    return toProper(s);
}

bn::string<128> game_controller::sick(int m, bn::string<128> s)
{
    switch (m)
    {
        case -5:
        case 5:
            return "dead " + s;
        case -4:
        case 4:
            return "comatose " + s;
        case -3:
        case 3:
            return "crippled " + s;
        case -2:
        case 2:
            return "sick " + s;
        case -1:
        case 1:
            return "undernourished " + s;
    }
}

bn::string<128> game_controller::young(int m, bn::string<128> s)
{
    switch (m)
    {
        case -5:
        case 5:
            return "foetal " + s;
        case -4:
        case 4:
            return "baby " + s;
        case -3:
        case 3:
            return "preadolescent " + s;
        case -2:
        case 2:
            return "teenage " + s;
        case -1:
        case 1:
            return "underage " + s;
    }
}

bn::string<128> game_controller::big(int m, bn::string<128> s)
{
    switch (m)
    {
        case -5:
        case 5:
            return "titanic " + s;
        case -4:
        case 4:
            return "giant " + s;
        case -3:
        case 3:
            return "enormous " + s;
        case -2:
        case 2:
            return "massive " + s;
        case -1:
        case 1:
            return "greater " + s;
    }
}

bn::string<128> game_controller::special(int m, bn::string<128> s)
{
    switch (m)
    {
        case -5:
        case 5:
            return "demon " + s;
        case -4:
        case 4:
            return "undead " + s;
        case -3:
        case 3:
            if (s.find(' ') > 0)
            {
                return "warrior " + s;
            }
            else
            {
                return "Were-" + s;
            }
        case -2:
        case 2:
            return "cursed " + s;
        case -1:
        case 1:
            if (s.find(' ') > 0)
            {
                return "veteran " + s;
            }
            else
            {
                return "Battle-" + s;
            }
    }
}

item_struct game_controller::specialItem(player_struct& player, data_strings& data_strings)
{
    auto item = interestingItem(player, data_strings);
    item.typeId = item_struct::special;
    item.ofId = player.rng.get_unbiased_int(data_strings.item_of.size());
    return item;
}

item_struct game_controller::interestingItem(player_struct& player, data_strings& data_strings)
{
    return item_struct(player.rng.get_unbiased_int(data_strings.item_specials.size()), item_struct::interesting, player.rng.get_unbiased_int(data_strings.item_modifiers.size()));
}

item_struct game_controller::boringItem(player_struct& player, data_strings& data_strings)
{
    return item_struct(player.rng.get_unbiased_int(data_strings.items_boring.size()), item_struct::boring);
}

void game_controller::winItem(player_struct& player, data_strings& data_strings)
{
    int n = player.rng.get_unbiased_int(999);
    if ((250 > n ? 250 : n) < player.inventory.size())
    {
        player.inventory[player.rng.get_unbiased_int(player.inventory.size())].count++;
    }
    else
    {
        auto item = specialItem(player, data_strings);
        for (auto& i : player.inventory)
        {
            if (i.id == item.id && i.typeId == item.typeId && i.ofId == item.ofId)
            {
                i.count++;
                return;
            }
        }
        player.inventory.push_back(item);
    }
}

equipment_struct game_controller::lPick(bn::vector<bn::string_view, 38>& equipment, bn::vector<short, 38>& equipment_val, int goal, player_struct& player)
{
    unsigned short item_id = player.rng.get_unbiased_int(equipment.size());
    short item_val = equipment_val[item_id];
    for (int i = 0; i < 5; i++)
    {
        unsigned short item_t = player.rng.get_unbiased_int(equipment.size());
        short item_t_val = equipment_val[item_t];
        if ((goal - item_val) > (goal - item_t_val))
        {
            return equipment_struct(item_t, equipment_struct::weapon);
        }
    }
    return equipment_struct(item_id, equipment_struct::weapon);;
}

void game_controller::winEquip(player_struct& player, data_strings& data_strings)
{
    int posn = player.rng.get_unbiased_int(player.equipment.size());
    bn::vector<bn::string_view, 38>* stuff = &data_strings.equipment_armour;
    bn::vector<short, 38>* stuff_val = &data_strings.equipment_armour_val;
    bn::vector<bn::string_view, 38>* better = &data_strings.equipment_def;
    bn::vector<short, 38>* better_val = &data_strings.equipment_def_val;
    bn::vector<bn::string_view, 38>* worse = &data_strings.equipment_def_bad;
    bn::vector<short, 38>* worse_val = &data_strings.equipment_def_bad_val;
    if (posn == 0)
    {
        stuff = &data_strings.equipment_weapon;
        stuff_val = &data_strings.equipment_weapon_val;
        better = &data_strings.equipment_off;
        better_val = &data_strings.equipment_off_val;
        worse = &data_strings.equipment_off_bad;
        worse_val = &data_strings.equipment_off_bad_val;
    }
    else
    {
        stuff = &data_strings.equipment_shield;
        stuff_val = &data_strings.equipment_shield_val;
    }
    equipment_struct item = lPick(*stuff, *stuff_val, player.level, player);
    switch (posn)
    {
        case 0:
            item.modifierEquipTypeId = equipment_struct::weapon;
            break;
        case 1:
            item.modifierEquipTypeId = equipment_struct::shield;
            break;
        default:
            item.modifierEquipTypeId = equipment_struct::armour;
            break;
    }
    short qual = (*stuff_val)[item.equipId];
    int plus = player.level - qual;
    if (plus < 0)
    {
        better = worse;
        better_val = worse_val;
        item.modifierTypeId1 = equipment_struct::bad;
        item.modifierTypeId2 = equipment_struct::bad;
    }
    int count = 0;
    while ((count < 2) && (plus != 0))
    {
        if (count == 0)
        {
            item.modifierId1 = player.rng.get_unbiased_int((*better).size());
            qual = (*better_val)[item.modifierId1];
            item.plusMinus += qual;
        }
        else
        {
            item.modifierId2 = player.rng.get_unbiased_int((*better).size());
            qual = (*better_val)[item.modifierId2];
        }
        if (item.modifierId1 == item.modifierId2)
        {
            // Original documentation:
            // no repeats
            item.hasModifier2 = false;
            break;
        }
        else
        {
            item.hasModifier2 = true;
            item.plusMinus += qual;
        }
        if (bn::abs(plus) < bn::abs(qual))
        {
            // Original documentation:
            // too much
            break;
        }
        plus -= qual;
        count++;
    }
    switch (item.baseEquipTypeId)
    {
        case equipment_struct::weapon:
            item.plusMinus += data_strings.equipment_weapon_val[item.equipId];
            break;
        case equipment_struct::shield:
            item.plusMinus += data_strings.equipment_shield_val[item.equipId];
            break;
        case equipment_struct::armour:
            item.plusMinus += data_strings.equipment_armour_val[item.equipId];
            break;
        case equipment_struct::dummy:
            break;
    }

    player.equipment[posn] = item;
}

unsigned short game_controller::equipPrice(player_struct& player)
{
    return  5 * player.level * player.level
            + 10 * player.level
            + 20;
}

void game_controller::winSpell(player_struct& player, data_strings& data_strings)
{
    auto newSpellId = player.rng.get_unbiased_int(bn::min<unsigned int>(player.stats[4] + player.level, data_strings.spells.size()));
    for (auto& spell : player.spells)
    {
        if (spell.id == newSpellId)
        {
            spell.level++;
            return;
        }
    }
    player.spells.push_back(spell_struct(newSpellId, 1));
}

void game_controller::winStat(player_struct& player, data_strings& data_strings)
{
    int i = 0;
    if (player.rng.get_unbiased_int(2) < 1)
    {
        i = player.rng.get_unbiased_int(player.stats.size());
    }
    else
    {
        int t = 0;
        // Original documentation:
        // Favor the best stats so they will tend to clump
        for (int j = 0; j < 6; j++)
        {
            t += player.stats[j] * player.stats[j];
        }
        t = player.rng.get_unbiased_int(0x7FFFFFFF) % t;
        t = player.rng.get_unbiased_int(t);
        i--;
        while (t >= 0)
        {
            i++;
            t -= player.stats[i] * player.stats[i];
        }
    }
    player.stats[i]++;
    if (i == 0)
    {
        player.enc.max = bn::min<unsigned short>(256, player.stats[0] + 10);
    }
}

void game_controller::interplotCinematic(player_struct& player, data_strings& data_strings)
{
    switch (player.rng.get_unbiased_int(3))
    {
        case 0:
            q(progress_struct(progress_struct::task, 1, "Exhausted, you arrive at a friendly oasis in a hostile land"), player, data_strings);
            q(progress_struct(progress_struct::task, 2, "You greet old friends and meet new allies"), player, data_strings);
            q(progress_struct(progress_struct::task, 2, "You are privy to a council of powerful do-gooders"), player, data_strings);
            q(progress_struct(progress_struct::task, 1, "There is much to be done. You are chosen!"), player, data_strings);
            break;
        case 1:
        {
            q(progress_struct(progress_struct::task, 1, "Your quarry is in sight, but a mighty enemy bars your path!"), player, data_strings);
            auto nemesis = namedMonster(player, data_strings, player.level + 3);
            q(progress_struct(progress_struct::task, 4, "A desperate struggle commences with " + nemesis), player, data_strings);
            auto s = player.rng.get_unbiased_int(3);
            for (int i = 0; i < player.rng.get_unbiased_int(player.plot_queue.size() + 1); i++)
            {
                s += player.rng.get_unbiased_int(2) + 1;
                switch (s % 3)
                {
                    case 0:
                        q(progress_struct(progress_struct::task, 2, "Locked in grim combat with " + nemesis), player, data_strings);
                        break;
                    case 1:
                        q(progress_struct(progress_struct::task, 2, nemesis + " seems to have the upper hand"), player, data_strings);
                        break;
                    case 2:
                        q(progress_struct(progress_struct::task, 2, "You seem to gain the advantage over " + nemesis), player, data_strings);
                        break;
                }
            }
            q(progress_struct(progress_struct::task, 3, "Victory! " + nemesis + " is slain! Exhausted, you lose conciousness"), player, data_strings);
            q(progress_struct(progress_struct::task, 2, "You awake in a friendly place, but the road awaits"), player, data_strings);
            break;
        }
        case 2:
        {
            auto nemesis = impressiveGuy(player, data_strings);
            q(progress_struct(progress_struct::task, 2, "Oh sweet relief! You've reached the kind protection of " + nemesis), player, data_strings);
            q(progress_struct(progress_struct::task, 3, "There is rejoicing, and an unnerving encouter with " + nemesis + " in private"), player, data_strings);
            q(progress_struct(progress_struct::task, 2, "You forget your " + bn::string<128>(data_strings.items_boring[boringItem(player, data_strings).id]) + " and go back to get it"), player, data_strings);
            q(progress_struct(progress_struct::task, 2, "What's this!? You overhear something shocking!"), player, data_strings);
            q(progress_struct(progress_struct::task, 2, "Could " + nemesis + " be a dirty double-dealer?"), player, data_strings);
            q(progress_struct(progress_struct::task, 3, "Who can possibly be trusted with this news!? -- Oh yes, of course"), player, data_strings);
            break;
        }
    }
    q(progress_struct(progress_struct::plot, 2, "Loading"), player, data_strings);
}

bn::string<128> game_controller::namedMonster(player_struct& player, data_strings &data_strings, unsigned short monster_level)
{
    int lev = 0;
    bn::string<128> m;
    unsigned short l;
    bn::string<128> out = "";
    for (int i = 1; i < 6; i++)
    {
        auto r = player.rng.get_unbiased_int(data_strings.items_monster.size());
        m = data_strings.items_monster[r];
        l = data_strings.items_monster_val[r];
        if (out == "" || bn::abs<int>(monster_level - l) < bn::abs<int>(monster_level - lev))
        {
            out = split(m, 0);
            lev = l;
        }
    }
    return generateName(player) + " the " + out;
}

bn::string<128> game_controller::impressiveGuy(player_struct &player, data_strings &data_strings)
{
    bn::string<128> out = data_strings.titles_impressive[player.rng.get_unbiased_int(data_strings.titles_impressive.size())];
    switch (player.rng.get_unbiased_int(2))
    {
        case 0:
        {
            bn::string<128> s = data_strings.races[player.rng.get_unbiased_int(data_strings.races.size())];
            return "the " + out + " of the " + plural(split(s, 0));
        }
        case 1:
        {
            return out + " " + generateName(player) + " of " + generateName(player);
        }
    }
}

void game_controller::start(player_struct& player, data_strings& data_strings)
{
    player.exp.max = levelUpTime(1);

    player.task_data.caption = "load";
    player.quest_data.caption = "";
    player.message_queue.clear();

    task("Loading", 2, player);
    q(progress_struct(progress_struct::task, 10, "Experiencing an enigmatic and foreboding night vision"), player, data_strings);
    q(progress_struct(progress_struct::task, 6, "Much is revealed about that wise old bastard you'd underestimated"), player, data_strings);
    q(progress_struct(progress_struct::task, 6, "A shocking series of events leaves you alone and bewildered, but resolute"), player, data_strings);
    q(progress_struct(progress_struct::task, 4, "Drawing upon an unexpected reserve of determination, you set out on a long and dangerous journey"), player, data_strings);
    q(progress_struct(progress_struct::plot, 2, "Loading"), player, data_strings);

    player.plot_prog.max = 26;
    player.plot_queue.push_back(quest_struct("Prologue"));

    updateLists(player, data_strings);
}

void game_controller::tick(player_struct& player, data_strings& data_strings)
{
    auto gain = player.task_data.caption.find("kill|") == 0;
    if (player.task_prog.value >= player.task_prog.max)
    {
        // Original documentation:
        // gain XP / level up
        if (gain)
        {
            if (player.exp.value >= player.exp.max)
            {
                levelUp(player, data_strings);
            }
            else
            {
                player.exp.value += bn::fixed(player.task_prog.max).safe_division(60.f).round_integer();
            }
        }

        // Original documentation:
        // advance quest
        if (gain)
        {
            if (player.plot_queue.size() > 1)
            {
                if (player.quest_prog.value >= player.quest_prog.max || player.quest_queue.size() == 0)
                {
                    completeQuest(player, data_strings);
                }
                else if (player.quest_queue.size() > 0)
                {
                    player.quest_prog.value += bn::fixed(player.task_prog.max).safe_division(60.f).round_integer();
                    player.quest_prog.value = bn::min<unsigned short>(player.quest_prog.value, player.quest_prog.max);
                }
            }
        }

        // Original documentation:
        // advance plot
        if (gain && player.plot_prog.value >= player.plot_prog.max)
        {
            interplotCinematic(player, data_strings);
        }
        else if (player.task_data.caption != "load")
        {
            player.plot_prog.value = bn::min<unsigned short>(player.plot_prog.value + bn::fixed(player.task_prog.max).safe_division(60.f).round_integer(), player.plot_prog.max);
        }

        dequeueQ(player, data_strings);
    }
    else
    {
        player.task_prog.value += 1 + bn::core::last_missed_frames();
        player.task_prog.value = bn::min<unsigned short>(player.task_prog.value, player.task_prog.max);
        // player.elapsed = 0;
        updateLists(player, data_strings);
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
            case 3:
                drawTab4(player, data_strings);
                break;
        }
    }
}

void game_controller::saveGame(player_struct& player)
{
    // bn::sram::write(player);
}
