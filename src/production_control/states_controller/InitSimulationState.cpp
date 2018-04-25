//
// Created by don on 24-4-18.
//

#include <memory>
#include "InitSimulationState.h"


void States::InitSimulationState::doActivity() {
    context.run();
}

void States::InitSimulationState::entryAction() {
//    context.setCurrentState(std::make_shared<States::SimulationBroadcastState>());
}

void States::InitSimulationState::exitAction() {

}

bool States::InitSimulationState::handleEvent(const EventPtr &e) {
    return false;
}
