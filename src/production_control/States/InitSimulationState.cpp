//
// Created by don on 24-4-18.
//

#include <memory>
#include "InitSimulationState.h"
#include "SimulationBroadcastState.h"

bool InitSimulationState::handleEvent(const Patterns::Statemachine::Event &e, Patterns::Statemachine::Context &c) {
    return false;
}

void InitSimulationState::doActivity() {
    context.run();
}

void InitSimulationState::entryAction() {
    context.setCurrentState(std::make_shared<SimulationBroadcastState>());
}

void InitSimulationState::exitAction() {

}

InitSimulationState::InitSimulationState()
    :context(InitSimulationContext())
{

}
