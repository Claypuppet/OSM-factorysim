//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONWAITFORCONNECTIONSSTATE_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONWAITFORCONNECTIONSSTATE_H


#include <patterns/statemachine/State.h>

namespace States {
    class SimulationWaitForConnectionsState : public Patterns::Statemachine::State {
    public:
        bool handleEvent(const Patterns::Statemachine::Event &e, Patterns::Statemachine::Context &c) override;

        /**
         * Waits for machines to connect to the Application and sends relevant config data
         */
        void doActivity() override;

        void entryAction() override;

        void exitAction() override;
    };
}


#endif //PRODUCTION_LINE_CONTROL_SIMULATIONWAITFORCONNECTIONSSTATE_H
