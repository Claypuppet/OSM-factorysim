//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_WAITFORCONNECTIONSSTATE_H
#define PRODUCTION_LINE_CONTROL_WAITFORCONNECTIONSSTATE_H


#include <patterns/statemachine/State.h>

namespace States {
    class WaitForConnectionsState : public Patterns::Statemachine::State {
    public:
        WaitForConnectionsState() = default;

        bool handleEvent(const Patterns::Statemachine::Event &e) override;

        /**
         * Waits untill all configured machines are connected to the Application
         * Sends the relevant config to the machines
         */
        void doActivity() override;

        void entryAction() override;

        void exitAction() override;
    };
}


#endif //PRODUCTION_LINE_CONTROL_WAITFORCONNECTIONSSTATE_H
