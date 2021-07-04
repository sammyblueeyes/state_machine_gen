#include "BreadMachine.h"
#include <iostream>



int main() {
    BreadMachine bread_machine;
    std::cout << bread_machine;

    bread_machine.press_on_off_button();
    std::cout << bread_machine;
}
