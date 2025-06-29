#include "bn_core.h"

#include "menu_controller.h"

int main()
{
    bn::core::init();
    menu_controller menu;
    menu.enter();

    while(true)
    {
        menu.update();
        bn::core::update();
    }
}
