//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H
#define PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H


#include "../../ProductionState.h"

namespace ProductionStates::InOperation::ProcessProduct {
    class ProcessProductState : public ProductionState {
    public:
        ProcessProductState(Communication::NetworkComponent &aContext) : ProductionState(aContext) {};

        virtual ~ProcessProductState() = default;

        virtual void entryAction();


        virtual void doActivity();

        virtual void exitAction();
    };
}


#endif //PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H
