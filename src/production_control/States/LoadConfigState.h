//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_LOADCONFIGSTATE_H
#define PRODUCTION_LINE_CONTROL_LOADCONFIGSTATE_H


#include <patterns/statemachine/State.h>

namespace States {
    class LoadConfigState : public Patterns::Statemachine::State {
    public:
        LoadConfigState() = default;
        bool handleEvent(const Patterns::Statemachine::EventPtr &e) override;

        /**
         * Loads configuration and creates machine objects for the Application and SimulationController class
         */
        void doActivity() override;

        void entryAction() override;

        void exitAction() override;

    };
}

#endif //PRODUCTION_LINE_CONTROL_LOADCONFIGSTATE_H
