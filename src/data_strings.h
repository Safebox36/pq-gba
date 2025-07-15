#ifndef DATA_STRINGS_H
#define DATA_STRINGS_H

#include "bn_vector.h"
#include "bn_string_view.h"

class data_strings
{
    public:
        bn::vector<bn::string_view, 21> races = bn::vector<bn::string_view, 21>();
        bn::vector<bn::string_view, 18> classes = bn::vector<bn::string_view, 18>();
        bn::vector<bn::string_view, 8> stats = bn::vector<bn::string_view, 8>();
        bn::vector<bn::string_view, 45> spells = bn::vector<bn::string_view, 45>();
        bn::vector<bn::string_view, 11> equipment_titles = bn::vector<bn::string_view, 11>();
        bn::vector<bn::string_view, 38> equipment_weapon = bn::vector<bn::string_view, 38>();
        bn::vector<short, 38> equipment_weapon_val = bn::vector<short, 38>();
        bn::vector<bn::string_view, 16> equipment_shield = bn::vector<bn::string_view, 16>();
        bn::vector<short, 16> equipment_shield_val = bn::vector<short, 16>();
        bn::vector<bn::string_view, 20> equipment_armour = bn::vector<bn::string_view, 20>();
        bn::vector<short, 20> equipment_armour_val = bn::vector<short, 20>();
        bn::vector<bn::string_view, 11> equipment_off = bn::vector<bn::string_view, 11>();
        bn::vector<short, 11> equipment_off_val = bn::vector<short, 11>();
        bn::vector<bn::string_view, 9> equipment_def = bn::vector<bn::string_view, 9>();
        bn::vector<short, 9> equipment_def_val = bn::vector<short, 9>();
        bn::vector<bn::string_view, 9> equipment_off_bad = bn::vector<bn::string_view, 9>();
        bn::vector<short, 9> equipment_off_bad_val = bn::vector<short, 9>();
        bn::vector<bn::string_view, 14> equipment_def_bad = bn::vector<bn::string_view, 14>();
        bn::vector<short, 14> equipment_def_bad_val = bn::vector<short, 14>();

        data_strings()
        {
            races.push_back("Half Orc");
            races.push_back("Half Man");
            races.push_back("Half Halfling");
            races.push_back("Double Hobbit");
            races.push_back("Gobhobbit");
            races.push_back("Low Elf");
            races.push_back("Dung Elf");
            races.push_back("Talking Pony");
            races.push_back("Gyrognome");
            races.push_back("Lesser Dwarf");
            races.push_back("Crested Dwarf");
            races.push_back("Eel Man");
            races.push_back("Panda Man");
            races.push_back("Trans-Kobold");
            races.push_back("Ench'ed M'cycle");
            races.push_back("Will o' the Wisp");
            races.push_back("Battle-Finch");
            races.push_back("Double Wookiee");
            races.push_back("Skraeling");
            races.push_back("Demicanadian");
            races.push_back("Land Squid");

            classes.push_back("Ur-Paladin");
            classes.push_back("Voodoo Princess");
            classes.push_back("Robot Monk");
            classes.push_back("Mu-Fu Monk");
            classes.push_back("Mage Illusioner");
            classes.push_back("Shiv-Knight");
            classes.push_back("Inner Mason");
            classes.push_back("Fighter/Organist");
            classes.push_back("Puma Burgular");
            classes.push_back("Runeloremaster");
            classes.push_back("Hunter Strangler");
            classes.push_back("Battle-Felon");
            classes.push_back("Tickle-Mimic");
            classes.push_back("Slow Poisoner");
            classes.push_back("Bastard Lunatic");
            classes.push_back("Jungle Clown");
            classes.push_back("Birdrider");
            classes.push_back("Vermineer");

            stats.push_back("STR");
            stats.push_back("DEX");
            stats.push_back("CON");
            stats.push_back("INT");
            stats.push_back("WIS");
            stats.push_back("CHA");
            stats.push_back("HP Max");
            stats.push_back("MP Max");

            spells.push_back("Slime Finger");
            spells.push_back("Rabbit Punch");
            spells.push_back("Hastiness");
            spells.push_back("Good Move");
            spells.push_back("Sadness");
            spells.push_back("Seasick");
            spells.push_back("Shoelaces");
            spells.push_back("Inoculate");
            spells.push_back("Cone of/    Annoyance");
            spells.push_back("Magnetic Orb");
            spells.push_back("Invisible/    Hands");
            spells.push_back("Revolting/    Cloud");
            spells.push_back("Aqueous/    Humor");
            spells.push_back("Spectral/    Miasma");
            spells.push_back("Clever Fellow");
            spells.push_back("Lockjaw");
            spells.push_back("History/    Lesson");
            spells.push_back("Hydrophobia");
            spells.push_back("Big Sister");
            spells.push_back("Cone of Paste");
            spells.push_back("Mulligan");
            spells.push_back("Nestor's/    Bright Idea");
            spells.push_back("Holy Batpole");
            spells.push_back("Tumor/    (Benign)");
            spells.push_back("Braingate");
            spells.push_back("Nonplus");
            spells.push_back("Animate/    Nightstand");
            spells.push_back("Eye of the/    Troglodyte");
            spells.push_back("Curse Name");
            spells.push_back("Dropsy");
            spells.push_back("Vitreous/    Humor");
            spells.push_back("Roger's Grand/    Illusion");
            spells.push_back("Covet");
            spells.push_back("Astral Miasma");
            spells.push_back("Spectral/    Oyster");
            spells.push_back("Acrid Hands");
            spells.push_back("Angioplasty");
            spells.push_back("Grognor's Big/    Day Off");
            spells.push_back("Tumor/    (Malignant)");
            spells.push_back("Animate Tunic");
            spells.push_back("Ursine Armor");
            spells.push_back("Holy Roller");
            spells.push_back("Tonsillectomy");
            spells.push_back("Curse Family");
            spells.push_back("Infinite/    Confusion");

            equipment_titles.push_back("Weapon");
            equipment_titles.push_back("Shield");
            equipment_titles.push_back("Helm");
            equipment_titles.push_back("Hauberk");
            equipment_titles.push_back("Brassairts");
            equipment_titles.push_back("Vambraces");
            equipment_titles.push_back("Gauntlets");
            equipment_titles.push_back("Gambeson");
            equipment_titles.push_back("Cuisses");
            equipment_titles.push_back("Greaves");
            equipment_titles.push_back("Sollerets");

            equipment_weapon.push_back("Stick");
            equipment_weapon.push_back("Broken Bottle");
            equipment_weapon.push_back("Shiv");
            equipment_weapon.push_back("Sprig");
            equipment_weapon.push_back("Oxgoad");
            equipment_weapon.push_back("Eelspear");
            equipment_weapon.push_back("Bowie Knife");
            equipment_weapon.push_back("Claw Hammer");
            equipment_weapon.push_back("Handpeen");
            equipment_weapon.push_back("Andiron");
            equipment_weapon.push_back("Hatchet");
            equipment_weapon.push_back("Tomahawk");
            equipment_weapon.push_back("Hackbarm");
            equipment_weapon.push_back("Crowbar");
            equipment_weapon.push_back("Mace");
            equipment_weapon.push_back("Battleadze");
            equipment_weapon.push_back("Leafmace");
            equipment_weapon.push_back("Shortsword");
            equipment_weapon.push_back("Longiron");
            equipment_weapon.push_back("Poachard");
            equipment_weapon.push_back("Baselard");
            equipment_weapon.push_back("Whinyard");
            equipment_weapon.push_back("Blunderbuss");
            equipment_weapon.push_back("Longsword");
            equipment_weapon.push_back("Crankbow");
            equipment_weapon.push_back("Blibo");
            equipment_weapon.push_back("Broadsword");
            equipment_weapon.push_back("Kreen");
            equipment_weapon.push_back("Morning Star");
            equipment_weapon.push_back("Pole-adze");
            equipment_weapon.push_back("Spontoon");
            equipment_weapon.push_back("Bastard Sword");
            equipment_weapon.push_back("Peen-arm");
            equipment_weapon.push_back("Culverin");
            equipment_weapon.push_back("Lance");
            equipment_weapon.push_back("Halberd");
            equipment_weapon.push_back("Poleax");
            equipment_weapon.push_back("Bandyclef");

            equipment_weapon_val.push_back(0);
            equipment_weapon_val.push_back(1);
            equipment_weapon_val.push_back(1);
            equipment_weapon_val.push_back(1);
            equipment_weapon_val.push_back(1);
            equipment_weapon_val.push_back(2);
            equipment_weapon_val.push_back(2);
            equipment_weapon_val.push_back(2);
            equipment_weapon_val.push_back(2);
            equipment_weapon_val.push_back(3);
            equipment_weapon_val.push_back(3);
            equipment_weapon_val.push_back(3);
            equipment_weapon_val.push_back(3);
            equipment_weapon_val.push_back(4);
            equipment_weapon_val.push_back(4);
            equipment_weapon_val.push_back(4);
            equipment_weapon_val.push_back(5);
            equipment_weapon_val.push_back(5);
            equipment_weapon_val.push_back(5);
            equipment_weapon_val.push_back(5);
            equipment_weapon_val.push_back(5);
            equipment_weapon_val.push_back(6);
            equipment_weapon_val.push_back(6);
            equipment_weapon_val.push_back(6);
            equipment_weapon_val.push_back(6);
            equipment_weapon_val.push_back(7);
            equipment_weapon_val.push_back(7);
            equipment_weapon_val.push_back(7);
            equipment_weapon_val.push_back(8);
            equipment_weapon_val.push_back(8);
            equipment_weapon_val.push_back(8);
            equipment_weapon_val.push_back(9);
            equipment_weapon_val.push_back(9);
            equipment_weapon_val.push_back(10);
            equipment_weapon_val.push_back(10);
            equipment_weapon_val.push_back(11);
            equipment_weapon_val.push_back(12);
            equipment_weapon_val.push_back(15);

            equipment_shield.push_back("Parasol");
            equipment_shield.push_back("Pie Plate");
            equipment_shield.push_back("Garbage Can Lid");
            equipment_shield.push_back("Buckler");
            equipment_shield.push_back("Plexiglass");
            equipment_shield.push_back("Fender");
            equipment_shield.push_back("Round Shield");
            equipment_shield.push_back("Carapace");
            equipment_shield.push_back("Scutum");
            equipment_shield.push_back("Propugner");
            equipment_shield.push_back("Kite Shield");
            equipment_shield.push_back("Pavise");
            equipment_shield.push_back("Tower Shield");
            equipment_shield.push_back("Baroque Shield");
            equipment_shield.push_back("Aegis");
            equipment_shield.push_back("Magnetic Field");

            equipment_shield_val.push_back(0);
            equipment_shield_val.push_back(1);
            equipment_shield_val.push_back(2);
            equipment_shield_val.push_back(3);
            equipment_shield_val.push_back(4);
            equipment_shield_val.push_back(4);
            equipment_shield_val.push_back(5);
            equipment_shield_val.push_back(5);
            equipment_shield_val.push_back(6);
            equipment_shield_val.push_back(6);
            equipment_shield_val.push_back(7);
            equipment_shield_val.push_back(8);
            equipment_shield_val.push_back(9);
            equipment_shield_val.push_back(11);
            equipment_shield_val.push_back(12);
            equipment_shield_val.push_back(18);

            equipment_armour.push_back("Lace");
            equipment_armour.push_back("Macrame");
            equipment_armour.push_back("Burlap");
            equipment_armour.push_back("Canvas");
            equipment_armour.push_back("Flannel");
            equipment_armour.push_back("Chamois");
            equipment_armour.push_back("Pleathers");
            equipment_armour.push_back("Leathers");
            equipment_armour.push_back("Bearskin");
            equipment_armour.push_back("Ringmail");
            equipment_armour.push_back("Scale Mail");
            equipment_armour.push_back("Chainmail");
            equipment_armour.push_back("Splint Mail");
            equipment_armour.push_back("Platemail");
            equipment_armour.push_back("ABS");
            equipment_armour.push_back("Kevlar");
            equipment_armour.push_back("Titanium");
            equipment_armour.push_back("Mithril Mail");
            equipment_armour.push_back("Diamond Mail");
            equipment_armour.push_back("Plasma");

            equipment_armour_val.push_back(1);
            equipment_armour_val.push_back(2);
            equipment_armour_val.push_back(3);
            equipment_armour_val.push_back(4);
            equipment_armour_val.push_back(5);
            equipment_armour_val.push_back(6);
            equipment_armour_val.push_back(7);
            equipment_armour_val.push_back(8);
            equipment_armour_val.push_back(9);
            equipment_armour_val.push_back(10);
            equipment_armour_val.push_back(12);
            equipment_armour_val.push_back(14);
            equipment_armour_val.push_back(15);
            equipment_armour_val.push_back(16);
            equipment_armour_val.push_back(17);
            equipment_armour_val.push_back(18);
            equipment_armour_val.push_back(19);
            equipment_armour_val.push_back(20);
            equipment_armour_val.push_back(25);
            equipment_armour_val.push_back(30);

            equipment_off.push_back("Polished");
            equipment_off.push_back("Serrated");
            equipment_off.push_back("Heavy");
            equipment_off.push_back("Pronged");
            equipment_off.push_back("Steely");
            equipment_off.push_back("Vicious");
            equipment_off.push_back("Venomed");
            equipment_off.push_back("Stabbity");
            equipment_off.push_back("Dancing");
            equipment_off.push_back("Invisible");
            equipment_off.push_back("Vorpal");

            equipment_off_val.push_back(1);
            equipment_off_val.push_back(1);
            equipment_off_val.push_back(1);
            equipment_off_val.push_back(2);
            equipment_off_val.push_back(2);
            equipment_off_val.push_back(3);
            equipment_off_val.push_back(4);
            equipment_off_val.push_back(4);
            equipment_off_val.push_back(5);
            equipment_off_val.push_back(6);
            equipment_off_val.push_back(7);

            equipment_def.push_back("Studded");
            equipment_def.push_back("Banded");
            equipment_def.push_back("Gilded");
            equipment_def.push_back("Festooned");
            equipment_def.push_back("Holy");
            equipment_def.push_back("Cambric");
            equipment_def.push_back("Fine");
            equipment_def.push_back("Impressive");
            equipment_def.push_back("Custom");

            equipment_def_val.push_back(1);
            equipment_def_val.push_back(2);
            equipment_def_val.push_back(2);
            equipment_def_val.push_back(3);
            equipment_def_val.push_back(4);
            equipment_def_val.push_back(1);
            equipment_def_val.push_back(4);
            equipment_def_val.push_back(5);
            equipment_def_val.push_back(3);

            equipment_off_bad.push_back("Dull");
            equipment_off_bad.push_back("Tarnished");
            equipment_off_bad.push_back("Rusty");
            equipment_off_bad.push_back("Padded");
            equipment_off_bad.push_back("Bent");
            equipment_off_bad.push_back("Mini");
            equipment_off_bad.push_back("Rubber");
            equipment_off_bad.push_back("Nerf");
            equipment_off_bad.push_back("Unbalanced");

            equipment_off_bad_val.push_back(-2);
            equipment_off_bad_val.push_back(-1);
            equipment_off_bad_val.push_back(-3);
            equipment_off_bad_val.push_back(-5);
            equipment_off_bad_val.push_back(-4);
            equipment_off_bad_val.push_back(-4);
            equipment_off_bad_val.push_back(-6);
            equipment_off_bad_val.push_back(-7);
            equipment_off_bad_val.push_back(-2);

            equipment_def_bad.push_back("Holey");
            equipment_def_bad.push_back("Patched");
            equipment_def_bad.push_back("Threadbare");
            equipment_def_bad.push_back("Faded");
            equipment_def_bad.push_back("Rusty");
            equipment_def_bad.push_back("Motheaten");
            equipment_def_bad.push_back("Mildewed");
            equipment_def_bad.push_back("Torn");
            equipment_def_bad.push_back("Dented");
            equipment_def_bad.push_back("Cursed");
            equipment_def_bad.push_back("Plastic");
            equipment_def_bad.push_back("Cracked");
            equipment_def_bad.push_back("Warped");
            equipment_def_bad.push_back("Corroded");

            equipment_def_bad_val.push_back(-1);
            equipment_def_bad_val.push_back(-1);
            equipment_def_bad_val.push_back(-2);
            equipment_def_bad_val.push_back(-1);
            equipment_def_bad_val.push_back(-3);
            equipment_def_bad_val.push_back(-3);
            equipment_def_bad_val.push_back(-2);
            equipment_def_bad_val.push_back(-3);
            equipment_def_bad_val.push_back(-3);
            equipment_def_bad_val.push_back(-5);
            equipment_def_bad_val.push_back(-4);
            equipment_def_bad_val.push_back(-4);
            equipment_def_bad_val.push_back(-3);
            equipment_def_bad_val.push_back(-3);
        }

        bool isSpellMultiline(unsigned int i)
        {
            switch (i)
            {
                case 8:
                case 10:
                case 11:
                case 12:
                case 13:
                case 16:
                case 21:
                case 23:
                case 26:
                case 27:
                case 30:
                case 31:
                case 34:
                case 37:
                case 38:
                case 44:
                    return true;
                default:
                    return false;
            }
        }
};

#endif //DATA_STRINGS_H