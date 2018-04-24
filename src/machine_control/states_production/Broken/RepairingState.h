//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_REPAIRINGSTATE_H
#define PRODUCTION_LINE_CONTROL_REPAIRINGSTATE_H


#include "../ProductionState.h"

namespace ProductionStates::Broken {
    class RepairingState : public ProductionState {
    public:
        RepairingState(Communication::NetworkComponent &context);

        virtual ~RepairingState() = default;

        virtual void entryAction();


        virtual void doActivity();

        virtual void exitAction();
    };
}

#endif //PRODUCTION_LINE_CONTROL_REPAIRINGSTATE_H
