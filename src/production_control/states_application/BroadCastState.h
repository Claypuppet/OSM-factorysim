//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_BROADCASTSTATE_H
#define PRODUCTION_LINE_CONTROL_BROADCASTSTATE_H


#include "ApplicationState.h"

namespace ApplicationStates {
    class BroadCastState : public ApplicationState {
    public:
      BroadCastState(core::Application &context);


        void doActivity() override;

        bool handleEvent(const EventPtr &e) override;

        void entryAction() override;

        void exitAction() override;
    };
}

#endif //PRODUCTION_LINE_CONTROL_BROADCASTSTATE_H
