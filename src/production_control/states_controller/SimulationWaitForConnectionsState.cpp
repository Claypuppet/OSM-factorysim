//
// Created by don on 24-4-18.
//

#include <network/Connection.h>
#include "SimulationWaitForConnectionsState.h"
#include "OperationState.h"

States::SimulationWaitForConnectionsState::SimulationWaitForConnectionsState(simulation::SimulationController &context) :
        ControllerState(context)
{
}

void States::SimulationWaitForConnectionsState::entryAction() {
  context.setupNetwork();
}

void States::SimulationWaitForConnectionsState::doActivity() {

}

void States::SimulationWaitForConnectionsState::exitAction() {
  context.turnOnSimulationMachines();
}

bool States::SimulationWaitForConnectionsState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeMachineReady: {
      onMachineReady(event);
      break;
    }
    case kEventTypeMachineConnected: {
      onMachineConnected(event);
      break;
    }
    case kEventTypeAllMachinesReadyForSimulation: {
      onAllMachinesReadyForSimulation();
      break;
    }

    default:return ControllerState::handleEvent(event);
  }
}

void States::SimulationWaitForConnectionsState::onMachineReady(const States::EventPtr &event) {
  context.machineReady(event->getArgumentAsType<u_int16_t>(0));
}

void States::SimulationWaitForConnectionsState::onMachineConnected(const States::EventPtr &event) {
  context.registerMachine(event->getArgumentAsType<u_int16_t>(0), event->getArgumentAsType<Network::ConnectionPtr>(1));
}

void States::SimulationWaitForConnectionsState::onAllMachinesReadyForSimulation() {
  context.setCurrentState(std::make_shared<OperationState>(context));
}
