#include "BreadMachineStateMachine.h"
#include <iostream>

class BreadMachine: public BreadMachineStateMachine {
    public:
        void press_on_off_button();
        void press_start_button();
        void press_inc_delay_button();
        void press_dec_delay_button();

    private:
        void tick_and_print(BreadMachine::Event event);

        virtual turning_on_ret turning_on();
        virtual turning_off_ret turning_off();
        virtual handle_inc_delay_ret handle_inc_delay();
        virtual handle_dec_delay_ret handle_dec_delay();
        virtual start_mixing_ret start_mixing();
        virtual start_with_delay_ret start_with_delay();
        virtual start_first_proof_ret start_first_proof();
        virtual start_knock_down_ret start_knock_down();
        virtual start_second_proof_ret start_second_proof();
        virtual start_bake_ret start_bake();
        virtual start_keep_warm_ret start_keep_warm();
};


std::ostream& operator<<(std::ostream& os, const BreadMachine& bread_machine)
{
    os << "Current state: " << bread_machine.state_str() << "\n";
    return os;
}


void BreadMachine::press_on_off_button()
{
    std::cout << "*** Press ON/OFF Button ***\n";
    tick_and_print(BreadMachine::EVENT_ON_OFF_PRESSED);
}

void BreadMachine::press_start_button()
{
    std::cout << "*** Press START Button ***\n";
    tick_and_print(BreadMachine::EVENT_START_PRESSED);
}

void BreadMachine::press_inc_delay_button()
{
    std::cout << "*** Press INCREMENT DELAY Button ***\n";
    tick_and_print(BreadMachine::EVENT_INCREMENT_DELAY_PRESSED);
}

void BreadMachine::press_dec_delay_button()
{
    std::cout << "*** Press DECREMENT DELAY Button ***\n";
    tick_and_print(BreadMachine::EVENT_DECREMENT_DELAY_PRESSED);
}

void BreadMachine::tick_and_print(BreadMachine::Event event)
{
    tickMachine(event);
    std::cout << (*this);
}

BreadMachine::turning_on_ret BreadMachine::turning_on() {
    std::cout << "    turning_on\n";
    // TODO
    return turning_on_ret_SYM_OK;
}

BreadMachine::turning_off_ret BreadMachine::turning_off() {
    std::cout << "    turning_off\n";
    // TODO
    return turning_off_ret_SYM_OK;
}

BreadMachine::handle_inc_delay_ret BreadMachine::handle_inc_delay() {
    std::cout << "    handle_inc_delay\n";
    // TODO
    return handle_inc_delay_ret_SYM_READY_DELAY_START;
}

BreadMachine::handle_dec_delay_ret BreadMachine::handle_dec_delay() {
    std::cout << "    handle_dec_delay\n";
    // TODO
    return handle_dec_delay_ret_SYM_READY_DELAY_START;
}

BreadMachine::start_mixing_ret BreadMachine::start_mixing() {
    std::cout << "    start_mixing\n";
    // TODO
    return start_mixing_ret_SYM_OK;
}

BreadMachine::start_with_delay_ret BreadMachine::start_with_delay() {
    std::cout << "    start_with_delay\n";
    // TODO
    return start_with_delay_ret_SYM_OK;
}

BreadMachine::start_first_proof_ret BreadMachine::start_first_proof() {
    std::cout << "    start_first_proof\n";
    // TODO
    return start_first_proof_ret_SYM_OK;
}

BreadMachine::start_knock_down_ret BreadMachine::start_knock_down() {
    std::cout << "    start_knock_down\n";
    // TODO
    return start_knock_down_ret_SYM_OK;
}

BreadMachine::start_second_proof_ret BreadMachine::start_second_proof() {
    std::cout << "    start_second_proof\n";
    // TODO
    return start_second_proof_ret_SYM_OK;
}

BreadMachine::start_bake_ret BreadMachine::start_bake() {
    std::cout << "    start_bake\n";
    // TODO
    return start_bake_ret_SYM_OK;
}

BreadMachine::start_keep_warm_ret BreadMachine::start_keep_warm() {
    std::cout << "    start_keep_warm\n";
    // TODO
    return start_keep_warm_ret_SYM_OK;
}
