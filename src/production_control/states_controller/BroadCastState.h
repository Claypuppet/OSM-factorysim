//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_BROADCASTSTATE_H
#define PRODUCTION_LINE_CONTROL_BROADCASTSTATE_H


#include "ControllerState.h"

namespace States {
    class BroadCastState : public ControllerState {
    public:
        BroadCastState(Core::SimulationController &context) : ControllerState(context){};

        /**
         * Broadcasts the ip and port of the Application over the network
         */
        void doActivity() override;

        bool handleEvent(const EventPtr &e) override;

        void entryAction() override;

        void exitAction() override;
    };
}

#endif //PRODUCTION_LINE_CONTROL_BROADCASTSTATE_H
