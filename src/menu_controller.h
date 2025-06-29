#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

class menu_controller
{
    private:
        int selectedOption = 0;

    public:
        int getSelectedOption();
        void setSelectedOption(int option);

        void enter();
        void update();
        void exit();
};

#endif //MENU_CONTROLLER_H