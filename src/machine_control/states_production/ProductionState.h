//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_PRODUCTIONSTATE_H
#define PRODUCTION_LINE_CONTROL_PRODUCTIONSTATE_H

#include <patterns/statemachine/State.h>
#include "../NetworkComponent.h"

namespace ProductionStates {
    class ProductionState : public Patterns::Statemachine::State {
    public:
        virtual ~ProductionState() = default;

        virtual void entryAction() = 0;

        virtual void doActivity() = 0;

        virtual void exitAction() = 0;

        virtual bool handleEvent(const Patterns::Statemachine::EventPtr &e) = 0;

    protected:
        ProductionState(Patterns::Statemachine::Context& aContext);

        Patterns::Statemachine::Context& context;
    };

}

#endif //PRODUCTION_LINE_CONTROL_PRODUCTIONSTATE_H
