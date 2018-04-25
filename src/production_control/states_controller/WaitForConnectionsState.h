//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_WAITFORCONNECTIONSSTATE_H
#define PRODUCTION_LINE_CONTROL_WAITFORCONNECTIONSSTATE_H


#include "ControllerState.h"

namespace States {
    class WaitForConnectionsState : public ControllerState {
    public:
        WaitForConnectionsState(Core::SimulationController &context) : ControllerState(context){};

        bool handleEvent(const EventPtr &e) override;

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
