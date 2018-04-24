//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_BROKENSTATE_H
#define PRODUCTION_LINE_CONTROL_BROKENSTATE_H

#include "../ProductionState.h"

namespace ProductionStates {
    namespace Broken {
        class BrokenState : public ProductionState {
        public:
            BrokenState(Patterns::Statemachine::Context &aContext);

            virtual ~BrokenState() = default;

            virtual void entryAction();


            virtual void doActivity();

            virtual void exitAction();
        };
    }
}

#endif //PRODUCTION_LINE_CONTROL_BROKENSTATE_H
