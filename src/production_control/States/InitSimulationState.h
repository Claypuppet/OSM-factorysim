//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_INITSIMULATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_INITSIMULATIONSTATE_H


#include <patterns/statemachine/State.h>
#include "patterns/statemachine/Context.h"

namespace States {
    class InitSimulationContext : public Patterns::Statemachine::Context {
    public:
        InitSimulationContext() = default;

        ~InitSimulationContext() = default;
    };

    class InitSimulationState : public Patterns::Statemachine::State {
    public:
        InitSimulationState();

        bool handleEvent(const Patterns::Statemachine::Event &e, Patterns::Statemachine::Context &c) override;

        /**
         * Handles the doActivity of the contexts state
         */
        void doActivity() override;

        /**
         * Sets state to SimulationBroadcastState
         */
        void entryAction() override;

        void exitAction() override;

    private:
        InitSimulationContext context;
    };
}

#endif //PRODUCTION_LINE_CONTROL_INITSIMULATIONSTATE_H
