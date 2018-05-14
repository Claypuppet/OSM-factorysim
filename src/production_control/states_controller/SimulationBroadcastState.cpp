//
// Created by don on 24-4-18.
//

#include "SimulationBroadcastState.h"
#include "SimulationWaitForConnectionsState.h"


states::SimulationBroadcastState::SimulationBroadcastState(simulation::SimulationController &context) :
		ControllerState(context)
{
}

void states::SimulationBroadcastState::doActivity() {

    // temp move directly to next state
    context.setCurrentState(std::make_shared<SimulationWaitForConnectionsState>(context));
}

void states::SimulationBroadcastState::entryAction() {
    // TODO: start UDP server
}

void states::SimulationBroadcastState::exitAction() {

}

bool states::SimulationBroadcastState::handleEvent(const EventPtr &e) {
    return false;
}
