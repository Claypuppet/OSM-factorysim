//
// Created by klei on 5/16/18.
//

#include <utils/time/Time.h>
#include <utils/Logger.h>
#include "SimulationApplication.h"
#include "states_application/WaitForConnectionsState.h"
#include "NotificationTypes.h"

namespace simulation {

static const uint64_t eightHoursInMillis = 28800000;

SimulationApplication::SimulationApplication() : scheduledStateEvents(false) {

}

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
  // Check if we are still waiting for responses...
  for (const auto &machine : getSimulationMachines()) {
    if (machine->isWaitingForSimulationResponse()) {
      return;
    }
  }

  scheduleMachineNotifications();

  if (!scheduledStateEvents){
    Application::executeScheduler();
  }

  // Temp, print statistics of machines etc. every few hours. move to
  static auto logMoment = utils::Time::getInstance().getCurrentTime();
  auto current = utils::Time::getInstance().getCurrentTime();
  if (current > logMoment) {
    logMoment = current + eightHoursInMillis; // log again in ~8 hours
    logStatistics();
  }
}

void SimulationApplication::logStatistics() const {
  std::stringstream stream;
  stream << "!Status update: current time: " << utils::Time::getInstance().getCurrentTimeString() << std::endl;
  stream << " Products:" << std::endl;
  for (const auto &product : productionLine->getProducts()) {
    stream << "  \"" << product->getName() << "\" total produced: "
           << lastMachineInLine.at(product->getId())->getAmountProcessed(product->getId()) << std::endl;
  }
  stream << " Machines:" << std::endl;
  for (const auto &machine : machines) {
    stream << "  \"" << machine->getName() << "\" " << std::endl
           << "   current status: " << machine->getStatus() << std::endl
           << "   times broke: " << machine->getTimesBroken() << std::endl
           << "   Spend time in states:" << std::endl;
    for (const auto &stateSpend : machine->getTimeSpendInState()) {
      stream << "    " << stateSpend.first << ": " << stateSpend.second << std::endl;
    }
  }
  // Log to console for now
  utils::Logger::log(stream.str());
}

const std::vector<SimulationMachinePtr> SimulationApplication::getSimulationMachines() const {
  std::vector<SimulationMachinePtr> list;
  for (const auto &machine : machines) {
    list.emplace_back(std::dynamic_pointer_cast<SimulationMachine>(machine));
  }
  return list;
}

void SimulationApplication::scheduleMachineNotifications() {
  auto simulationMachines = getSimulationMachines();

  bool foundEvents = false;
  uint64_t lowestTime = 0;

  for (const auto &machine : simulationMachines) {
    auto machineEventTime = machine->getNextEventMoment();
    if (machineEventTime && !foundEvents) {
      lowestTime = machineEventTime;
      foundEvents = true;
    } else if (machineEventTime != 0 && machineEventTime < lowestTime) {
      lowestTime = machineEventTime;
    }
  }
  if (foundEvents) {
    utils::Time::getInstance().syncTime(lowestTime);
    for (const auto &machine : simulationMachines) {
      // Get events for this machine on lowest time
      auto delayedNotifications = machine->getEvents(lowestTime);
      for (const auto &notification : delayedNotifications) {
        Application::handleNotification(notification);
      }
    }
    scheduledStateEvents = true;
  } else{
    scheduledStateEvents = false;
  }
}

}