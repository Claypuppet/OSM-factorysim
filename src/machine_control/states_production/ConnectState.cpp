//
// Created by sven on 23-4-18.
//

#include "ConnectState.h"

namespace ProductionStates {
    void ConnectState::entryAction() {
        //TODO: START CLIENT AND CONNECT TO PRODUCTION CONTROL
    }

    void ConnectState::doActivity() {

    }

    void ConnectState::exitAction() {
        //TODO: START CONFIGURESTATE
    }

    bool ConnectState::handleEvent(const Patterns::Statemachine::Event &e) {
        return false;
    }
}