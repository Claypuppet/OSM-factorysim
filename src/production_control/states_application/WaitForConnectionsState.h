//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_WAITFORCONNECTIONSSTATE_H
#define PRODUCTION_LINE_CONTROL_WAITFORCONNECTIONSSTATE_H


#include "ApplicationState.h"

namespace ApplicationStates {
    class WaitForConnectionsState : public ApplicationState {
    public:
        WaitForConnectionsState(core::Application &context);
        virtual ~WaitForConnectionsState() = default;

        bool handleEvent(const ApplicationStates::EventPtr &event) override;

        /**
         * Waits untill all configured machines are connected to the Application
         * Sends the relevant config to the machines
         */
        void doActivity() override;

        void entryAction() override;

        void exitAction() override;

     private:
      void onMachineReady(const ApplicationStates::EventPtr &event);
      void onAllMachinesReady();
    };
}


#endif //PRODUCTION_LINE_CONTROL_WAITFORCONNECTIONSSTATE_H
