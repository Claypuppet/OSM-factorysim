//
// Created by don on 24-4-18.
//

#include <memory>
#include "ConnectMachinesState.h"
#include "BroadCastState.h"

States::ConnectMachinesState::ConnectMachinesState()
    :context(States::ConnectMachinesContext())
{

}

bool States::ConnectMachinesState::handleEvent(const Patterns::Statemachine::Event &e, Patterns::Statemachine::Context &c) {
    return false;
}

void States::ConnectMachinesState::doActivity() {
    context.run();
}

void States::ConnectMachinesState::entryAction() {
    context.setCurrentState(std::make_shared<States::BroadCastState>());
}

void States::ConnectMachinesState::exitAction() {

}
