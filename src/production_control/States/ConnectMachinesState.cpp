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

void States::ConnectMachinesState::doActivity() {
    context.run();
}

void States::ConnectMachinesState::entryAction() {
    context.setCurrentState(std::make_shared<States::BroadCastState>(States::BroadCastState()));
}

void States::ConnectMachinesState::exitAction() {

}

bool States::ConnectMachinesState::handleEvent(const Patterns::Statemachine::EventPtr &e) {
    return false;
}
