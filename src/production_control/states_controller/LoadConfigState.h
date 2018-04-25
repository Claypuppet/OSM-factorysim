//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_LOADCONFIGSTATE_H
#define PRODUCTION_LINE_CONTROL_LOADCONFIGSTATE_H


#include "ControllerState.h"

namespace States {
    class LoadConfigState : public ControllerState {
    public:
        LoadConfigState(Core::SimulationController &context) : ControllerState(context){};
        bool handleEvent(const EventPtr &e) override;

        /**
         * Loads configuration and creates machine objects for the Application and SimulationController class
         */
        void doActivity() override;

        void entryAction() override;

        void exitAction() override;

    };
}

#endif //PRODUCTION_LINE_CONTROL_LOADCONFIGSTATE_H
