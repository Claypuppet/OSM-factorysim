
#ifndef PRODUCTION_LINE_CONTROL_OPERATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_OPERATIONSTATE_H

// project file includes
#include "ControllerState.h"

namespace States {
    class OperationState : public ControllerState {
    public:
        OperationState(simulation::SimulationController &aContext);

        /**
         * Runs the simulation
         */
        void doActivity() override;
        void entryAction() override;
        bool handleEvent(const EventPtr &event) override;
        void exitAction() override;
    };
}


#endif //PRODUCTION_LINE_CONTROL_OPERATIONSTATE_H
