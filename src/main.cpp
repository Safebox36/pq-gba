#include "bn_core.h"

#include "player_struct.h"
#include "data_strings.h"
#include "menu_controller.h"
#include "create_controller.h"
#include "game_controller.h"

int main()
{
    bn::core::init();
    int activeScreen = 0;
    int nextScreen = 0;
    player_struct player = player_struct();
    data_strings data_str = data_strings();
    menu_controller menu;
    create_controller create;
    game_controller game;
    menu.enter();

    while(true)
    {
        switch(activeScreen)
        {
            case 0:
                menu.update(nextScreen);
                break;
            case 1:
                create.update(nextScreen, player, data_str);
                break;
            case 2:
                game.update(player, data_str);
                break;
        }
        if (activeScreen != nextScreen)
        {
            switch (nextScreen)
            {
                case 0:
                    menu.enter();
                    activeScreen = 0;
                    break;
                case 1:
                    create.enter(player, data_str);
                    activeScreen = 1;
                    break;
                case 2:
                    game.enter(player, data_str);
                    activeScreen = 2;
                    break;
            }
        }
        bn::core::update();
    }
}
