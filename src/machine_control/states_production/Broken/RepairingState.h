//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_REPAIRINGSTATE_H
#define PRODUCTION_LINE_CONTROL_REPAIRINGSTATE_H


#include "../ProductionState.h"

namespace ProductionStates {
    namespace Broken {
        class RepairingState : public ProductionState {
        public:
            RepairingState(Patterns::Statemachine::Context &aContext) : ProductionState(aContext) {};

            virtual ~RepairingState() = default;

            virtual void entryAction();


            virtual void doActivity();

            virtual void exitAction();
        };
    }
}

#endif //PRODUCTION_LINE_CONTROL_REPAIRINGSTATE_H