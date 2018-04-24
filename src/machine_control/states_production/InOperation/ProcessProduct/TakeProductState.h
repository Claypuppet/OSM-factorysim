//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_TAKEPRODUCTSTATE_H
#define PRODUCTION_LINE_CONTROL_TAKEPRODUCTSTATE_H


#include "../../../NetworkComponent.h"
#include "../../ProductionState.h"

namespace ProductionStates::InOperation::ProcessProduct {
    class TakeProductState : public ProductionState {
    public:
        TakeProductState(Communication::NetworkComponent &context);

        virtual ~TakeProductState() = default;

        virtual void entryAction();


        virtual void doActivity();

        virtual void exitAction();

    };
}


#endif //PRODUCTION_LINE_CONTROL_TAKEPRODUCTSTATE_H
