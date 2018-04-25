//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H
#define PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H


#include "../../ProductionState.h"

namespace ProductionStates {
    namespace InOperation {
        namespace ProcessProduct {
            class ProcessProductState : public ProductionState {
            public:
                ProcessProductState(Patterns::Statemachine::Context &aContext) : ProductionState(aContext) {};

                virtual ~ProcessProductState() = default;

                virtual void entryAction();


                virtual void doActivity();

                virtual void exitAction();
            };
        }
    }
}


#endif //PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H
