//
// Created by don on 24-4-18.
//

#include <network/Connection.h>
#include <utils/Logger.h>
#include "SimulationWaitForConnectionsState.h"
#include "OperationState.h"

states::SimulationWaitForConnectionsState::SimulationWaitForConnectionsState(simulation::SimulationController &context)
    :
        ControllerState(context)
{
}

void states::SimulationWaitForConnectionsState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
    context.setupNetwork();
}

void states::SimulationWaitForConnectionsState::doActivity() {

}

void states::SimulationWaitForConnectionsState::exitAction() {

}

bool states::SimulationWaitForConnectionsState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeMachineReady: {
      utils::Logger::log("-Handle event: kEventTypeMachineReady");
      onMachineReady(event);
      break;
    }
    case kEventTypeMachineConnected: {
      utils::Logger::log("-Handle event: kEventTypeMachineConnected");
      onMachineConnected(event);
      break;
    }
    case kEventTypeAllMachinesReadyForSimulation: {
      utils::Logger::log("-Handle event: kEventTypeAllMachinesReadyForSimulation");
      onAllMachinesReadyForSimulation();
      break;
    }

    default:return ControllerState::handleEvent(event);
  }
}

void states::SimulationWaitForConnectionsState::onMachineReady(const states::EventPtr &event) {
  context.machineReady(event->getArgumentAsType<u_int16_t>(0));
}

void states::SimulationWaitForConnectionsState::onMachineConnected(const states::EventPtr &event) {
  context.registerMachine(event->getArgumentAsType<u_int16_t>(0), event->getArgumentAsType<Network::ConnectionPtr>(1));
}

void states::SimulationWaitForConnectionsState::onAllMachinesReadyForSimulation() {
  context.setCurrentState(std::make_shared<OperationState>(context));
}
