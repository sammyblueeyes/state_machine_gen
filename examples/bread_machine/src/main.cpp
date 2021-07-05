#include "BreadMachine.h"
#include <iostream>


enum Button 
{
    BUTTON_ON_OFF,
    BUTTON_START,
    BUTTON_INC_DELAY,
    BUTTON_DEC_DELAY,
    BUTTON_MAX,
};

std::string button_text(const Button button) 
{
    switch(button) {
        case BUTTON_ON_OFF:
            return "BUTTON_ON_OFF";
        case BUTTON_START:
            return "BUTTON_START";
        case BUTTON_INC_DELAY:
            return "BUTTON_INC_DELAY";
        case BUTTON_DEC_DELAY:
            return "BUTTON_DEC_DELAY";
    };
    // TODO ERROR
}


Button parse_button_input(int input) 
{
    if (input < 0 || input >= BUTTON_MAX) {
        // TODO ERROR
    }
    return static_cast<Button>(input - 1);
}

void press_button(BreadMachine& bread_machine, Button button)
{
    switch (button) {
        case BUTTON_ON_OFF:
            bread_machine.press_on_off_button();
            break;
        case BUTTON_START:
            bread_machine.press_start_button();
            break;
        case BUTTON_INC_DELAY:
            bread_machine.press_inc_delay_button();
            break;
        case BUTTON_DEC_DELAY:
            bread_machine.press_dec_delay_button();
            break;
        case BUTTON_MAX:
            break;
    };
}


int main() 
{
    BreadMachine bread_machine;

    std::cout << "Welcome to the Bread Machine simulator :-)\n";

    while (true) {
        std::cout << "\n\n";
        std::cout << "Please press a button. Options are:\n";
        std::cout << "    1) on/off\n";
        std::cout << "    2) start\n";
        std::cout << "    3) increment delay\n";
        std::cout << "    4) decrement delay\n";

        int input;
        std::cin >> input;
        Button button = parse_button_input(input);
        std::cout << "You chose " << button_text(button) << "\n";
        press_button(bread_machine, button);
    }
}
