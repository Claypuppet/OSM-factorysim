//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONBROADCASTSTATE_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONBROADCASTSTATE_H


#include <patterns/statemachine/State.h>

namespace States {
    class SimulationBroadcastState : public Patterns::Statemachine::State {
    public:

        /**
         * Broadcasts the ip and port of the SimulationControll component over the network
         */
        void doActivity() override;

        bool handleEvent(const Patterns::Statemachine::EventPtr &e) override;

        void entryAction() override;

        void exitAction() override;
    };
}


#endif //PRODUCTION_LINE_CONTROL_SIMULATIONBROADCASTSTATE_H
