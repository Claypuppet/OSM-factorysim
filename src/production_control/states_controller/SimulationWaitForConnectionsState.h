//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONWAITFORCONNECTIONSSTATE_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONWAITFORCONNECTIONSSTATE_H


#include "ControllerState.h"

namespace states {
    class SimulationWaitForConnectionsState : public ControllerState {
    public:
        SimulationWaitForConnectionsState(simulation::SimulationController &context);

        bool handleEvent(const EventPtr &e) override;

        /**
         * Waits for machines to connect to the Application and sends relevant config data
         */
        void doActivity() override;

        void entryAction() override;

        void exitAction() override;
    };
}


#endif //PRODUCTION_LINE_CONTROL_SIMULATIONWAITFORCONNECTIONSSTATE_H
