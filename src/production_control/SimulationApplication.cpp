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

SimulationApplication::SimulationApplication() : canScheduleNotifications(false), simulationMachines(){

}

void SimulationApplication::setMachines(const std::vector<core::MachinePtr> &aMachines) {
  Application::setMachines(aMachines);

  // Add machines as simulation machines
  for (const auto &machine : machines) {
    simulationMachines.emplace_back(std::dynamic_pointer_cast<SimulationMachine>(machine));
  }
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
    case NotifyEventIds::eApplicationNOK:
    case NotifyEventIds::eApplicationProductTakenFromBuffer:
    case NotifyEventIds::eApplicationProductAddedToBuffer: {
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
  auto machineItr = std::find_if(simulationMachines.begin(), simulationMachines.end(),
                                 [machineId](const SimulationMachinePtr &machine){return machine->getId() == machineId;});
  return (simulationMachines.end() == machineItr) ? nullptr : *machineItr;
}

void SimulationApplication::executeScheduler() {
  // Check if we are still waiting for responses...
  for (const auto &machine : simulationMachines) {
    if (machine->isWaitingForSimulationResponse()) {
      return;
    }
  }

  if(canScheduleNotifications && scheduleMachineNotifications()){
    return;
  }

  Application::executeScheduler();
  canScheduleNotifications = true;

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

const std::vector<SimulationMachinePtr> &SimulationApplication::getSimulationMachines() const {
  return simulationMachines;
}

bool SimulationApplication::scheduleMachineNotifications() {
  uint64_t nextLowestTime = 0;
  for (const auto &machine : simulationMachines) {
    // Get events for this machine on lowest time
    auto nextMachineEventMoment = machine->getNextEventMoment();
    if (nextMachineEventMoment != 0 && (nextLowestTime == 0 || nextMachineEventMoment < nextLowestTime)) {
      nextLowestTime = nextMachineEventMoment;
    }
  }

  if (nextLowestTime != 0) {
    utils::Time::getInstance().syncTime(nextLowestTime);
    std::vector<patterns::notifyobserver::NotifyEvent> delayedNotifications;
    for (const auto &machine : simulationMachines) {
      // Get events for this machine on lowest time
      machine->getEvents(nextLowestTime, delayedNotifications);
    }
    for (const auto &notification : delayedNotifications) {
      Application::handleNotification(notification);
    }
    canScheduleNotifications = false;
    return true;
  }
  canScheduleNotifications = true;
  return false;
}

}