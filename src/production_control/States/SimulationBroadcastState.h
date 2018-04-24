//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONBROADCASTSTATE_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONBROADCASTSTATE_H


#include <patterns/statemachine/State.h>

namespace States {
    class SimulationBroadcastState : public Patterns::Statemachine::State {
    public:
        bool handleEvent(const Patterns::Statemachine::Event &e, Patterns::Statemachine::Context &c) override;

        /**
         * Broadcasts the ip and port of the SimulationControll component over the network
         */
        void doActivity() override;

        void entryAction() override;

        void exitAction() override;
    };
}


#endif //PRODUCTION_LINE_CONTROL_SIMULATIONBROADCASTSTATE_H
