//
// Created by don on 24-4-18.
//

#include <network/Connection.h>
#include "SimulationWaitForConnectionsState.h"
#include "OperationState.h"

States::SimulationWaitForConnectionsState::SimulationWaitForConnectionsState(Simulation::SimulationController &context)
    : ControllerState(context) {
}

void States::SimulationWaitForConnectionsState::entryAction() {
  context.setupNetwork();
}

void States::SimulationWaitForConnectionsState::doActivity() {

}

void States::SimulationWaitForConnectionsState::exitAction() {
  context.turnOnSimulationMachines();
}

bool States::SimulationWaitForConnectionsState::handleEvent(const EventPtr &e) {
  switch (e->getId()) {
    case kEventTypeMachineReady: {
      onMachineReady(e);
      break;
    }
    case kEventTypeMachineConnected: {
      onMachineConnected(e);
      break;
    }
    case kEventTypeAllMachinesReadyForSimulation: {
      onAllMachinesReadyForSimulation();
      break;
    }

    default:return ControllerState::handleEvent(e);
  }
}

void States::SimulationWaitForConnectionsState::onMachineReady(const States::EventPtr &e) {
  context.machineReady(e->getArgumentAsType<u_int16_t>(0));
}

void States::SimulationWaitForConnectionsState::onMachineConnected(const States::EventPtr &e) {
  context.registerMachine(e->getArgumentAsType<u_int16_t>(0), e->getArgumentAsType<Network::ConnectionPtr>(1));
}

void States::SimulationWaitForConnectionsState::onAllMachinesReadyForSimulation() {
  context.setCurrentState(std::make_shared<OperationState>(context));
}
