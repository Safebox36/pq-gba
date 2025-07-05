#include "bn_core.h"

#include "player_struct.h"
#include "menu_controller.h"
#include "create_controller.h"
#include "game_controller.h"

int main()
{
    bn::core::init();
    int activeScreen = 0;
    int nextScreen = 0;
    player_struct player = player_struct();
    menu_controller menu;
    create_controller create;
    // game_controller game;
    menu.enter();

    while(true)
    {
        switch(activeScreen)
        {
            case 0:
                menu.update(nextScreen);
                break;
            case 1:
                create.update(nextScreen, player);
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
                    create.enter(player);
                    activeScreen = 1;
                    break;
                // case 2:
                //     game.enter();
                //     break;
            }
        }
        bn::core::update();
    }
}
