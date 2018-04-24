//
// Created by don on 24-4-18.
//

#include "WaitForConnectionsState.h"

bool States::WaitForConnectionsState::handleEvent(const Patterns::Statemachine::Event &e, Patterns::Statemachine::Context &c) {
    return false;
}

/**
 * Waits untill all configured machines are connected to the SimulationControll component
 * Sends simulation configuration to all connected machines
 */
void States::WaitForConnectionsState::doActivity() {

}

void States::WaitForConnectionsState::entryAction() {

}

void States::WaitForConnectionsState::exitAction() {

}
