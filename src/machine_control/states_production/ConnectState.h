//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONNECTSTATE_H
#define PRODUCTION_LINE_CONTROL_CONNECTSTATE_H


#include "ProductionState.h"

namespace ProductionStates {
    class ConnectState : public ProductionState {
    public:
      ConnectState(MachineCore::Application &aContext)
                : ProductionState(aContext) {};

        virtual ~ConnectState() = default;

        virtual void entryAction();

        virtual void doActivity();

        virtual void exitAction();

        virtual bool handleEvent(const Patterns::Statemachine::EventPtr &e);
    };
}


#endif //PRODUCTION_LINE_CONTROL_CONNECTSTATE_H
