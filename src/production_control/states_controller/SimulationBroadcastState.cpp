//
// Created by don on 24-4-18.
//

#include "SimulationBroadcastState.h"
#include "SimulationWaitForConnectionsState.h"

void States::SimulationBroadcastState::doActivity() {

    // temp move directly to next state
    context.setCurrentState(std::make_shared<SimulationWaitForConnectionsState>(context));
}

void States::SimulationBroadcastState::entryAction() {
    // TODO: start UDP server
}

void States::SimulationBroadcastState::exitAction() {

}

bool States::SimulationBroadcastState::handleEvent(const EventPtr &e) {
    return false;
}
