//
// Created by sven on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_RECONFIGURESTATE_H
#define PRODUCTION_LINE_CONTROL_RECONFIGURESTATE_H


#include "../ProductionState.h"

namespace ProductionStates::InOperation {
    class ReConfigureState : public ProductionState {
    public:
        ReConfigureState(Communication::NetworkComponent &aContext) : ProductionState(aContext) {};

        virtual ~ReConfigureState() = default;

        virtual void entryAction();


        virtual void doActivity();

        virtual void exitAction();
    };
}


#endif //PRODUCTION_LINE_CONTROL_RECONFIGURESTATE_H
