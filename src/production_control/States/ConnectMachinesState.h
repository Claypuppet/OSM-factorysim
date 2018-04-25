//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONNECTMACHINESSTATE_H
#define PRODUCTION_LINE_CONTROL_CONNECTMACHINESSTATE_H


#include <patterns/statemachine/State.h>
#include "patterns/statemachine/Context.h"

namespace States {

    class ConnectMachinesContext : public Patterns::Statemachine::Context {
    public:
        ConnectMachinesContext() = default;

        ~ConnectMachinesContext() = default;
    };

    class ConnectMachinesState : public Patterns::Statemachine::State {
    public:
        ConnectMachinesState();

        /**
         * Handles the doActivity of the context state
         */
        void doActivity() override;

        bool handleEvent(const Patterns::Statemachine::EventPtr &e) override;

        /**
         * Sets the state of context to BroadcastState
         */
        void entryAction() override;

        void exitAction() override;

    private:
        ConnectMachinesContext context;
    };
}

#endif //PRODUCTION_LINE_CONTROL_CONNECTMACHINESSTATE_H
