//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_INITSIMULATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_INITSIMULATIONSTATE_H


#include "ControllerState.h"

namespace States {
    class InitSimulationState : public ControllerState {
    public:
		InitSimulationState(Core::SimulationController &context) : ControllerState(context){};
        /**
         * Handles the doActivity of the contexts state
         */
        void doActivity() override;

        bool handleEvent(const EventPtr &e) override;

        /**
         * Sets state to SimulationBroadcastState
         */
        void entryAction() override;

        void exitAction() override;

    };
}

#endif //PRODUCTION_LINE_CONTROL_INITSIMULATIONSTATE_H
