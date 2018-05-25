//
// Created by klei on 5/16/18.
//

#include "SimulationApplication.h"
#include "states_application/WaitForConnectionsState.h"
#include "NotificationTypes.h"

namespace simulation {

void SimulationApplication::turnOnSimulationMachines() {
  for (const auto &machine : machines) {
    auto simMachine = std::dynamic_pointer_cast<SimulationMachine>(machine);
    if (simMachine) {
      simMachine->sendTurnOnCommand();
    }
  }
}

void SimulationApplication::turnOffSimulationMachines() {
  for (const auto &machine : machines) {
    auto simMachine = std::dynamic_pointer_cast<SimulationMachine>(machine);
    if (simMachine) {
      simMachine->sendTurnOnCommand();
    }
  }
}

void SimulationApplication::setupNetwork() {
  Application::setupNetwork();
  turnOnSimulationMachines();
}
void SimulationApplication::handleNotification(const patterns::notifyobserver::NotifyEvent &notification) {
  switch (notification.getEventId()) {

    case NotifyEventIds::eApplicationOK:
    case NotifyEventIds::eApplicationNOK: {
      auto id = notification.getArgumentAsType<uint16_t>(1);
      auto machine = getSimulationMachine(id);
      machine->addEvent(notification);
      break;
    }
    default: {
      Application::handleNotification(notification);
      break;
    }
  }
}
SimulationMachinePtr SimulationApplication::getSimulationMachine(uint16_t machineId) {
  auto machine = getMachine(machineId);
  return std::dynamic_pointer_cast<SimulationMachine>(machine);
}

}