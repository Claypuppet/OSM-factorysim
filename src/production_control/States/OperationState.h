//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_OPERATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_OPERATIONSTATE_H


#include <patterns/statemachine/State.h>

namespace States {
    class OperationState : public Patterns::Statemachine::State {
    public:
        bool handleEvent(const Patterns::Statemachine::Event &e, Patterns::Statemachine::Context &c) override;

        /**
         * Runs the simulation
         */
        void doActivity() override;

        void entryAction() override;

        void exitAction() override;
    };
}


#endif //PRODUCTION_LINE_CONTROL_OPERATIONSTATE_H
