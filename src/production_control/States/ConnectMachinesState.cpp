//
// Created by don on 24-4-18.
//

#include "ConnectMachinesState.h"
#include "BroadCastState.h"

ConnectMachinesState::ConnectMachinesState()
    :context(ConnectMachinesContext())
{

}

bool ConnectMachinesState::handleEvent(const Patterns::Statemachine::Event &e, Patterns::Statemachine::Context &c) {
    return false;
}

void ConnectMachinesState::doActivity() {
    context.run();
}

void ConnectMachinesState::entryAction() {
    context.setCurrentState(std::make_shared<BroadCastState>());
}

void ConnectMachinesState::exitAction() {

}
