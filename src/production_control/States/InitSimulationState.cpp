//
// Created by don on 24-4-18.
//

#include <memory>
#include "InitSimulationState.h"
#include "SimulationBroadcastState.h"

bool States::InitSimulationState::handleEvent(const Patterns::Statemachine::Event &e, Patterns::Statemachine::Context &c) {
    return false;
}

void States::InitSimulationState::doActivity() {
    context.run();
}

void States::InitSimulationState::entryAction() {
    context.setCurrentState(std::make_shared<States::SimulationBroadcastState>());
}

void States::InitSimulationState::exitAction() {

}

InitSimulationState::InitSimulationState()
    :context(States::InitSimulationContext())
{

}
