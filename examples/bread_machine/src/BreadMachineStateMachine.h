#include <string>
#include <queue>
#include <memory>


class StateMachineLogger {
    public:
        virtual void log_transition(std::string from_state, std::string to_state) = 0;
};


class BreadMachineStateMachine {
    protected:
        enum turning_on_ret {
            turning_on_ret_SYM_ERROR,
            turning_on_ret_SYM_OK,
        };
        virtual turning_on_ret turning_on() = 0;

        enum turning_off_ret {
            turning_off_ret_SYM_OK,
        };
        virtual turning_off_ret turning_off() = 0;

        enum handle_inc_delay_ret {
            handle_inc_delay_ret_SYM_READY_DELAY_START,
        };
        virtual handle_inc_delay_ret handle_inc_delay() = 0;

        enum handle_dec_delay_ret {
            handle_dec_delay_ret_SYM_READY,
            handle_dec_delay_ret_SYM_READY_DELAY_START,
        };
        virtual handle_dec_delay_ret handle_dec_delay() = 0;

        enum start_mixing_ret {
            start_mixing_ret_SYM_ERROR,
            start_mixing_ret_SYM_OK,
        };
        virtual start_mixing_ret start_mixing() = 0;

        enum start_with_delay_ret {
            start_with_delay_ret_SYM_OK,
        };
        virtual start_with_delay_ret start_with_delay() = 0;

        enum start_first_proof_ret {
            start_first_proof_ret_SYM_OK,
        };
        virtual start_first_proof_ret start_first_proof() = 0;

        enum start_knock_down_ret {
            start_knock_down_ret_SYM_OK,
        };
        virtual start_knock_down_ret start_knock_down() = 0;

        enum start_second_proof_ret {
            start_second_proof_ret_SYM_OK,
        };
        virtual start_second_proof_ret start_second_proof() = 0;

        enum start_bake_ret {
            start_bake_ret_SYM_OK,
        };
        virtual start_bake_ret start_bake() = 0;

        enum start_keep_warm_ret {
            start_keep_warm_ret_SYM_OK,
        };
        virtual start_keep_warm_ret start_keep_warm() = 0;

    public:
        enum State {
            STATE_off,
            STATE_ready,
            STATE_ready_delay_start,
            STATE_wait_delayed_start,
            STATE_mixing,
            STATE_first_proof,
            STATE_knock_down,
            STATE_second_proof,
            STATE_baking,
            STATE_keep_warm,
            STATE_error,
        };

        enum Event {
            EVENT_ON_OFF_PRESSED,
            EVENT_START_PRESSED,
            EVENT_INCREMENT_DELAY_PRESSED,
            EVENT_DECREMENT_DELAY_PRESSED,
            EVENT_TIMEOUT,
        };

        BreadMachineStateMachine() :
            logger()
        {}

        BreadMachineStateMachine(std::unique_ptr<StateMachineLogger> _logger) :
                logger(std::move(_logger))
        {}

        std::string state_str() const;
        void tickMachine(Event event);

    private:
        State cur_state = STATE_off;
        std::queue<Event> next_event;
        std::unique_ptr<StateMachineLogger> logger;

        void kickMachine();
        std::string state_str(const State& state) const;
};


std::string BreadMachineStateMachine::state_str() const
{
    return state_str(cur_state);
}


std::string BreadMachineStateMachine::state_str(const State& state) const
{
    switch (state) {
        case STATE_off:
            return "STATE_off";
        case STATE_ready:
            return "STATE_ready";
        case STATE_ready_delay_start:
            return "STATE_ready_delay_start";
        case STATE_wait_delayed_start:
            return "STATE_wait_delayed_start";
        case STATE_mixing:
            return "STATE_mixing";
        case STATE_first_proof:
            return "STATE_first_proof";
        case STATE_knock_down:
            return "STATE_knock_down";
        case STATE_second_proof:
            return "STATE_second_proof";
        case STATE_baking:
            return "STATE_baking";
        case STATE_keep_warm:
            return "STATE_keep_warm";
        case STATE_error:
            return "STATE_error";
    };
    return "";
}


void BreadMachineStateMachine::tickMachine(Event event)
{
    // Using the queue allows tickMachine to be re-entrant.
    // TODO To make tickMachine thread safe, we'll also need locking
    if (next_event.empty()) {
        // We're not currenting executing kickMachine
        next_event.push(event);
        kickMachine(); 
        return;
    }
    // Already procesing events, so just queue the next one
    next_event.push(event);
}


void BreadMachineStateMachine::kickMachine() 
{
    while (!next_event.empty()) {
        Event event = next_event.front();
        next_event.pop();
        State next_state = cur_state;
        switch (cur_state) {
            case STATE_off:
                switch(event) {
                    case EVENT_ON_OFF_PRESSED:
                        switch(turning_on()) {
                            case turning_on_ret_SYM_ERROR:
                                next_state = STATE_error;
                                break;
                            case turning_on_ret_SYM_OK:
                                next_state = STATE_ready;
                                break;
                        };
                        break;
                    case EVENT_START_PRESSED:
                        break;
                    case EVENT_INCREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_DECREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_TIMEOUT:
                        break;
                };
                break;
            case STATE_ready:
                switch(event) {
                    case EVENT_ON_OFF_PRESSED:
                        switch (turning_off()) {
                            case turning_off_ret_SYM_OK:
                                next_state = STATE_off;
                                break;
                        };
                        break;
                    case EVENT_START_PRESSED:
                        break;
                    case EVENT_INCREMENT_DELAY_PRESSED:
                        switch(handle_inc_delay()) {
                            case handle_inc_delay_ret_SYM_READY_DELAY_START:
                                next_state = STATE_ready_delay_start;
                                break;
                        }
                        break;
                    case EVENT_DECREMENT_DELAY_PRESSED:
                        switch(handle_dec_delay()) {
                            case handle_dec_delay_ret_SYM_READY:
                                next_state = STATE_ready;
                                break;
                            case handle_dec_delay_ret_SYM_READY_DELAY_START:
                                next_state = STATE_ready_delay_start;
                                break;
                        }
                        break;
                    case EVENT_TIMEOUT:
                        break;
                };
                break;
            case STATE_ready_delay_start:
                switch(event) {
                    case EVENT_ON_OFF_PRESSED:
                        switch (turning_off()) {
                            case turning_off_ret_SYM_OK:
                                next_state = STATE_off;
                                break;
                        };
                        break;
                    case EVENT_START_PRESSED:
                        switch (start_with_delay()) {
                            case start_with_delay_ret_SYM_OK:
                                next_state = STATE_wait_delayed_start;
                                break;
                        };
                        break;
                    case EVENT_INCREMENT_DELAY_PRESSED:
                        switch(handle_inc_delay()) {
                            case handle_inc_delay_ret_SYM_READY_DELAY_START:
                                next_state = STATE_ready_delay_start;
                                break;
                        }
                        break;
                    case EVENT_DECREMENT_DELAY_PRESSED:
                        switch(handle_dec_delay()) {
                            case handle_dec_delay_ret_SYM_READY:
                                next_state = STATE_ready;
                                break;
                            case handle_dec_delay_ret_SYM_READY_DELAY_START:
                                next_state = STATE_ready_delay_start;
                                break;
                        }
                        break;
                    case EVENT_TIMEOUT:
                        break;
                };
                break;
            case STATE_wait_delayed_start:
                switch(event) {
                    case EVENT_ON_OFF_PRESSED:
                        break;
                    case EVENT_START_PRESSED:
                        break;
                    case EVENT_INCREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_DECREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_TIMEOUT:
                        switch (start_mixing()) {
                            case start_mixing_ret_SYM_ERROR:
                                next_state = STATE_error;
                                break;
                            case start_mixing_ret_SYM_OK:
                                next_state = STATE_mixing;
                                break;
                        };
                        break;
                };
                break;
            case STATE_mixing:
                switch(event) {
                    case EVENT_ON_OFF_PRESSED:
                        break;
                    case EVENT_START_PRESSED:
                        break;
                    case EVENT_INCREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_DECREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_TIMEOUT:
                        switch (start_first_proof()) {
                            case start_first_proof_ret_SYM_OK:
                                next_state = STATE_first_proof;
                                break;
                        };
                        break;
                };
                break;
            case STATE_first_proof:
                switch(event) {
                    case EVENT_ON_OFF_PRESSED:
                        break;
                    case EVENT_START_PRESSED:
                        break;
                    case EVENT_INCREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_DECREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_TIMEOUT:
                        switch (start_knock_down()) {
                            case start_knock_down_ret_SYM_OK:
                                next_state = STATE_knock_down;
                                break;
                        };
                        break;
                };
                break;
            case STATE_knock_down:
                switch(event) {
                    case EVENT_ON_OFF_PRESSED:
                        break;
                    case EVENT_START_PRESSED:
                        break;
                    case EVENT_INCREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_DECREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_TIMEOUT:
                        switch (start_second_proof()) {
                            case start_second_proof_ret_SYM_OK:
                                next_state = STATE_second_proof;
                                break;
                        };
                        break;
                };
                break;
            case STATE_second_proof:
                switch(event) {
                    case EVENT_ON_OFF_PRESSED:
                        break;
                    case EVENT_START_PRESSED:
                        break;
                    case EVENT_INCREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_DECREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_TIMEOUT:
                        switch (start_bake()) {
                            case start_bake_ret_SYM_OK:
                                next_state = STATE_baking;
                                break;
                        }
                        break;
                };
                break;
            case STATE_baking:
                switch(event) {
                    case EVENT_ON_OFF_PRESSED:
                        break;
                    case EVENT_START_PRESSED:
                        break;
                    case EVENT_INCREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_DECREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_TIMEOUT:
                        switch (start_keep_warm()) {
                            case start_keep_warm_ret_SYM_OK:
                                next_state = STATE_keep_warm;
                                break;
                        };
                        break;
                };
                break;
            case STATE_keep_warm:
                switch(event) {
                    case EVENT_ON_OFF_PRESSED:
                        break;
                    case EVENT_START_PRESSED:
                        break;
                    case EVENT_INCREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_DECREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_TIMEOUT:
                        // TODO: Find a way to consolodate the similar code for the transitions?
                        // In my previous work this was done using the same state enum
                        switch (turning_off()) {
                            case turning_off_ret_SYM_OK:
                                next_state = STATE_off;
                                break;
                        };
                        break;
                };
                break;
            case STATE_error:
                switch(event) {
                    case EVENT_ON_OFF_PRESSED:
                        // TODO: Duplicated from STATE_keep_warm
                        switch (turning_off()) {
                            case turning_off_ret_SYM_OK:
                                next_state = STATE_off;
                                break;
                        };
                        break;
                    case EVENT_START_PRESSED:
                        break;
                    case EVENT_INCREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_DECREMENT_DELAY_PRESSED:
                        break;
                    case EVENT_TIMEOUT:
                        break;
                };
                break;
        };

        if (logger) {
            logger->log_transition(state_str(cur_state), state_str(next_state));
        }
        cur_state = next_state;
    }
}
