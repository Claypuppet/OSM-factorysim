//
// Created by klei on 5/16/18.
//

#include <utils/time/Time.h>
#include "SimulationApplication.h"
#include "states_application/WaitForConnectionsState.h"
#include "NotificationTypes.h"

namespace simulation {

void SimulationApplication::turnOnSimulationMachines() {
  for (const auto &machine : getSimulationMachines()) {
    machine->sendTurnOnCommand();
  }
}

void SimulationApplication::turnOffSimulationMachines() {
  for (const auto &machine : getSimulationMachines()) {
    machine->sendTurnOnCommand();
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

void SimulationApplication::executeScheduler() {
  for (const auto &machine : getSimulationMachines()){
    if(machine->isWaitingForSimulationResponse()){
      return;
    }
  }
  scheduleMachineNotifications();
  Application::executeScheduler();
}

const std::vector<SimulationMachinePtr> SimulationApplication::getSimulationMachines() const {
  std::vector<SimulationMachinePtr> list;
  for(const auto &machine : machines){
    list.emplace_back(std::dynamic_pointer_cast<SimulationMachine>(machine));
  }
  return list;
}

void SimulationApplication::scheduleMachineNotifications() {
  auto simulationMachines = getSimulationMachines();

  bool foundEvents = false;
  uint64_t lowestTime = 0;

  for (const auto &machine : simulationMachines){
    auto machineEventTime = machine->getNextEventMoment();
    if(machineEventTime && !foundEvents){
      lowestTime = machineEventTime;
      foundEvents = true;
    }
    else if (machineEventTime != 0 && machineEventTime < lowestTime) {
      lowestTime = machineEventTime;
    }
  }
  if (foundEvents){
    utils::Time::getInstance().syncTime(lowestTime);
    for(const auto &machine : simulationMachines){
      // Get events for this machine on lowest time
      auto delayedNotifications = machine->getEvents(lowestTime);
      for (const auto &notification : delayedNotifications) {
        Application::handleNotification(notification);
      }
    }
  }
}

}