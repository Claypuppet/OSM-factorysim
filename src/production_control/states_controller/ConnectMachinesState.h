//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONNECTMACHINESSTATE_H
#define PRODUCTION_LINE_CONTROL_CONNECTMACHINESSTATE_H


#include "ControllerState.h"

namespace States {

    class ConnectMachinesState : public ControllerState {
    public:
        ConnectMachinesState(Core::SimulationController &context) : ControllerState(context){};

        /**
         * Handles the doActivity of the context state
         */
        void doActivity() override;

        bool handleEvent(const EventPtr &e) override;

        /**
         * Sets the state of context to BroadcastState
         */
        void entryAction() override;

        void exitAction() override;

    };
}

#endif //PRODUCTION_LINE_CONTROL_CONNECTMACHINESSTATE_H
