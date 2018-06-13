//
// Created by klei on 5/16/18.
//

#include <utils/time/Time.h>
#include <utils/Logger.h>
#include <utils/TimeHelper.h>
#include "SimulationApplication.h"
#include "states_application/WaitForConnectionsState.h"
#include "NotificationTypes.h"
#include "states_application/in_operation/PrepareShutdownState.h"

namespace simulation {

static const uint64_t eightHoursInMillis = 28800000;

SimulationApplication::SimulationApplication() : canScheduleNotifications(false), simulationMachines() {

}

void SimulationApplication::setMachines(const std::vector<core::MachinePtr> &aMachines) {
  Application::setMachines(aMachines);

  // Add machines as simulation machines
  for (const auto &machine : machines) {
    simulationMachines.emplace_back(std::dynamic_pointer_cast<SimulationMachine>(machine));
  }
}

void SimulationApplication::turnOnSimulationMachines() {
  for (const auto &machine : simulationMachines) {
    machine->sendTurnOnCommand();
  }
}

void SimulationApplication::turnOffSimulationMachines() {
  for (const auto &machine : simulationMachines) {
    machine->sendTurnOffCommand();
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
                                 [machineId](const SimulationMachinePtr &machine) {
                                   return machine->getId() == machineId;
                                 });
  return (simulationMachines.end() == machineItr) ? nullptr : *machineItr;
}

void SimulationApplication::executeScheduler() {
  // Check if we are still waiting for responses...
  for (const auto &machine : simulationMachines) {
    if (machine->isWaitingForSimulationResponse()) {
      return;
    }
  }

  if (canScheduleNotifications && scheduleMachineNotifications()) {
    return;
  }
  Application::executeScheduler();

  canScheduleNotifications = true;
}

const std::vector<SimulationMachinePtr> &SimulationApplication::getSimulationMachines() const {
  return simulationMachines;
}

bool SimulationApplication::scheduleMachineNotifications() {
  uint64_t nextLowestTime = 0;
  bool foundEvents = false;
  for (const auto &machine : simulationMachines) {
    // Get events for this machine on lowest time
    auto nextMachineEventMoment = machine->getNextEventMoment();
    if (nextMachineEventMoment != 0 && (nextLowestTime == 0 || nextMachineEventMoment < nextLowestTime)) {
      nextLowestTime = nextMachineEventMoment;
      foundEvents = true;
    }
  }

  // Make sure we dont go over next work day hours
  if (foundEvents && nextLowestTime > utils::TimeHelper::getInstance().getStartOfNextWorkDay()) {
    // for now schedule all disconnected event so shutdown can continue
    createAndScheduleStateEvent(applicationstates::kEventTypeAllMachinesDisconnected);
    return false;
  }

  if (foundEvents) {
    utils::Time::getInstance().syncTime(nextLowestTime);

    // Check if closing time.
    if (!std::dynamic_pointer_cast<applicationstates::PrepareShutdownState>(currentState)
        && utils::TimeHelper::getInstance().isClosingTime()) {
      createAndScheduleStateEvent(applicationstates::kEventTypeWorkDayOver);
      return true;
    }

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

void SimulationApplication::workDayOver() {
  Application::workDayOver();
}

void SimulationApplication::checkTimeToStartAgain() {
  Application::checkTimeToStartAgain();
  auto &timeHelper = utils::TimeHelper::getInstance();
  auto weekBeforeNextDay = timeHelper.getCurrentWeek();
  timeHelper.goToNextWorkDay();

  if (timeHelper.getCurrentWeek() > weekBeforeNextDay) {
    saveMachineStatistics();
    debugLogCurrentStats();
  }
  createAndScheduleStateEvent(applicationstates::kEventTypeNewWorkDayStarted);
}

void SimulationApplication::debugLogCurrentStats() {
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
      for(const auto &item : stateSpend.second) {
        stream << "    " << stateSpend.first << ": " << item.first << ": " << item.second << std::endl;
      }
    }
  }
  // Log to console for now
  utils::Logger::log(stream.str());
}

bool SimulationApplication::checkAllMachinesDisconnected() {
  // Send turn off to machines that are ready to be turned off
  for (const auto &machine : simulationMachines) {
    if (machine->isConnected() && machine->isIdle(false)) {
      machine->sendTurnOffCommand();
    }
  }
  return Application::checkAllMachinesDisconnected();
}

}