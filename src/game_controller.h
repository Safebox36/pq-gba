#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "bn_rect_window.h"
#include "bn_vector.h"
#include "bn_fixed.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_string.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "player_struct.h"
#include "progress_struct.h"
#include "data_strings.h"

class game_controller
{
    private:
        int activeTab = 0;
        int highlightedScrollbar = 0;
        bn::optional<bn::regular_bg_item> background_1;
        bn::optional<bn::regular_bg_item> background_2;
        bn::optional<bn::regular_bg_item> background_3;
        bn::optional<bn::regular_bg_item> background_4;
        bn::optional<bn::regular_bg_ptr> active_background;

        bn::optional<bn::rect_window> tabs;
        bn::vector<bn::vector<bn::sprite_ptr, 8>, 4> titles;
        bn::optional<bn::sprite_text_generator> text_generator;
        bn::optional<bn::sprite_text_generator> bold_text_generator;
        bn::vector<bn::string_view, 4> title_strings;
        bn::optional<bn::sprite_item> scroll;
        bn::vector<bn::sprite_ptr, 4> scrollbars;
        bn::optional<bn::sprite_ptr> scroll_thumb;
        bn::vector<int, 2> scroll_values;
        bn::vector<bn::vector<bn::sprite_ptr, 32>, 2> player_data;
        bn::vector<bn::sprite_ptr, 32> player_data_labels;
        bn::vector<bn::sprite_ptr, 16> player_progress;
        bn::vector<bn::point, 2> player_data_default_positions;

        bn::vector<bn::string<32>, 61> spell_list;
        bn::vector<short, 45> spell_levels;
        bn::vector<bn::string<32>, 55> equip_list;
        bn::vector<bn::sprite_ptr, 30> task_prog_bar;
        bn::vector<bn::sprite_ptr, 29> sub_prog_bars;

        int lerp(bn::fixed v0, bn::fixed v1, bn::fixed t);

    public:
        bool incrementActiveTab();
        bool decrementActiveTab();
        bool incrementHighlightedScrollbar(player_struct& player);
        bool decrementHighlightedScrollbar();

        void updateScrollbar(player_struct& player);
        void updateLists(player_struct& player, data_strings& data_strings);
        bn::string<64> clipKill(player_struct& player);
        bn::string<64> clipQuest(bn::string<128>& quest);
        void drawTab1(player_struct& player, data_strings& data_strings);
        void drawTab2(player_struct& player, data_strings& data_strings);
        void drawTab3(player_struct& player, data_strings& data_strings);
        void drawTab4(player_struct& player, data_strings& data_strings);

        bool rome(unsigned int& n, unsigned int dn, bn::string<7>& s, bn::string<7> ds);
        bn::string<7> intToRome(unsigned int n);
        bn::string<64> buildItemName(const item_struct& item, data_strings& data_strings);

        unsigned short levelUpTime(unsigned short level);
        void levelUp(player_struct& player, data_strings& data_strings);
        void task(bn::string<128> message, unsigned short duration, player_struct& player);//, unsigned short level);
        void q(progress_struct data, player_struct& player, data_strings& data_strings);
        void dequeueQ(player_struct& player, data_strings& data_strings);
        void completeAct(player_struct& player, data_strings& data_strings);
        void completeQuest(player_struct& player, data_strings& data_strings);
        bn::string<128> monsterTask(unsigned short& monster_level, player_struct& player, data_strings& data_strings);
        bn::string<128> split(bn::string<128> s, int field, char seperator);
        bn::string<128> split(bn::string<128> s, int field);
        bn::string<64> toLower(bn::string<64>& s);
        bn::string<128> toProper(bn::string<128>& s);
        bn::string<128> indefinite(const bn::string<128>& s, unsigned short count);
        bn::string<128> definite(const bn::string<128>& s, unsigned short count);
        bn::string<128> plural(const bn::string<128>& s);
        bn::string<128> generateName(player_struct& player);
        bn::string<128> sick(int m, bn::string<128> s);
        bn::string<128> young(int m, bn::string<128> s);
        bn::string<128> big(int m, bn::string<128> s);
        bn::string<128> special(int m, bn::string<128> s);
        item_struct specialItem(player_struct& player, data_strings& data_strings);
        item_struct interestingItem(player_struct& player, data_strings& data_strings);
        item_struct boringItem(player_struct& player, data_strings& data_strings);
        void winItem(player_struct& player, data_strings& data_strings);
        equipment_struct lPick(bn::vector<bn::string_view, 38>& equipment, bn::vector<short, 38>& equipment_val, int goal, player_struct& player);
        void winEquip(player_struct& player, data_strings& data_strings);
        unsigned short equipPrice(player_struct& player);
        void winSpell(player_struct& player, data_strings& data_strings);
        void winStat(player_struct& player, data_strings& data_strings);
        void interplotCinematic(player_struct& player, data_strings& data_strings);
        bn::string<128> namedMonster(player_struct& player, data_strings& data_strings, unsigned short monster_level);
        bn::string<128> impressiveGuy(player_struct& player, data_strings& data_strings);

        void enter(player_struct& player, data_strings& data_strings);
        void update(player_struct& player, data_strings& data_strings);
        void start(player_struct& player, data_strings& data_strings);
        void tick(player_struct& player, data_strings& data_strings);
        void saveGame(player_struct& player);
};

#endif //GAME_CONTROLLER_H