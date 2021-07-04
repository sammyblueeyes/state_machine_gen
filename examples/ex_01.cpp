#include "BreadMachine.h"
#include <iostream>

class BreadMachine: public BreadMachineStateMachine {
    private:
        virtual turning_on_ret turning_on() {
            std::cout << "    turning_on\n";
            // TODO
            return turning_on_ret_SYM_OK;
        }

        virtual turning_off_ret turning_off() {
            std::cout << "    turning_off\n";
            // TODO
            return turning_off_ret_SYM_OK;
        }

        virtual handle_inc_delay_ret handle_inc_delay() {
            std::cout << "    handle_inc_delay\n";
            // TODO
            return handle_inc_delay_ret_SYM_READY_DELAY_START;
        }

        virtual handle_dec_delay_ret handle_dec_delay() {
            std::cout << "    handle_dec_delay\n";
            // TODO
            return handle_dec_delay_ret_SYM_READY_DELAY_START;
        }

        virtual start_mixing_ret start_mixing() {
            std::cout << "    start_mixing\n";
            // TODO
            return start_mixing_ret_SYM_OK;
        }

        virtual start_with_delay_ret start_with_delay() {
            std::cout << "    start_with_delay\n";
            // TODO
            return start_with_delay_ret_SYM_OK;
        }

        virtual start_first_proof_ret start_first_proof() {
            std::cout << "    start_first_proof\n";
            // TODO
            return start_first_proof_ret_SYM_OK;
        }

        virtual start_knock_down_ret start_knock_down() {
            std::cout << "    start_knock_down\n";
            // TODO
            return start_knock_down_ret_SYM_OK;
        }

        virtual start_second_proof_ret start_second_proof() {
            std::cout << "    start_second_proof\n";
            // TODO
            return start_second_proof_ret_SYM_OK;
        }

        virtual start_bake_ret start_bake() {
            std::cout << "    start_bake\n";
            // TODO
            return start_bake_ret_SYM_OK;
        }

        virtual start_keep_warm_ret start_keep_warm() {
            std::cout << "    start_keep_warm\n";
            // TODO
            return start_keep_warm_ret_SYM_OK;
        }
};


std::ostream& operator<<(std::ostream& os, const BreadMachine& bread_machine)
{
    os << "Current state: " << bread_machine.state_str() << "\n";
    return os;
}



void tick_and_print(BreadMachine& bread_machine, BreadMachine::Event event)
{
    bread_machine.tickMachine(event);
    std::cout << bread_machine;
}


int main() {
    BreadMachine bread_machine;
    std::cout << bread_machine;

    tick_and_print(bread_machine, BreadMachine::EVENT_ON_OFF_PRESSED);
    tick_and_print(bread_machine, BreadMachine::EVENT_START_PRESSED);
    tick_and_print(bread_machine, BreadMachine::EVENT_INCREMENT_DELAY_PRESSED);
    tick_and_print(bread_machine, BreadMachine::EVENT_DECREMENT_DELAY_PRESSED);
    tick_and_print(bread_machine, BreadMachine::EVENT_TIMEOUT);
}


