//
// Created by don on 24-4-18.
//

#include <memory>
#include "ConnectMachinesState.h"
#include "BroadCastState.h"

ApplicationStates::ConnectMachinesState::ConnectMachinesState(core::Application &context) : ApplicationState(context) {

}

void ApplicationStates::ConnectMachinesState::doActivity() {
//    context.run();
}

void ApplicationStates::ConnectMachinesState::entryAction() {
//    context.setCurrentState(std::make_shared<ApplicationStates::BroadCastState>(ApplicationStates::BroadCastState()));
}

void ApplicationStates::ConnectMachinesState::exitAction() {

}

bool ApplicationStates::ConnectMachinesState::handleEvent(const EventPtr &e) {
    return false;
}