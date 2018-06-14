//
// Created by klei on 6/11/18.
//

#include <utils/time/Time.h>
#include <utils/RandomHelper.h>

#include "SimulationMachineLocal.h"
#include "NotificationTypes.h"

namespace simulation {

const uint16_t oneMinuteInMillis = 60000;
const uint16_t checkCycle = oneMinuteInMillis;
const uint64_t magicalNumber = 0;

SimulationMachineLocal::SimulationMachineLocal(const models::Machine &aMachine)
    : SimulationMachine(aMachine),
      connected(false),
      timeSinceBrokenCheck(utils::Time::getInstance().getCurrentTime()),
      momentOfLastItemProcessed(0),
      currentConfig() {
  // Set distributions
  uint64_t maxNumber = +(getMeanTimeBetweenFailureInMillis() / checkCycle);
  breakDistribution = utils::UnsignedUniformDistribution(magicalNumber, maxNumber);
  repairDistribution = utils::NormalDistribution(getReparationTimeInMinutes(), getReparationTimeStddevInMinutes());
}

bool SimulationMachineLocal::isSimulationConnected() const {
  return true;
}

bool SimulationMachineLocal::isReadyForSimulation() const {
  return true;
}

void SimulationMachineLocal::sendTurnOnCommand() {
  auto currentTime = utils::Time::getInstance().getCurrentTime();
  notifyRegisterMachine(currentTime);
  timeSinceBrokenCheck = currentTime;
}

void SimulationMachineLocal::sendTurnOffCommand() {
  notifyMachineDisconnected(utils::Time::getInstance().getCurrentTime());
  connected = false;
}

bool SimulationMachineLocal::isConnected() const {
  return connected;
}

void SimulationMachineLocal::setConnection(const network::ConnectionPtr &aConnection) {
  connected = true;
  setStatus(kMachineStatusInitializing);
  nextAction = kNextActionTypeIdle; // will be re-set by scheduler when preparing reconfigure
  momentOfLastItemProcessed = utils::Time::i().getCurrentTime();
}

void SimulationMachineLocal::sendStartProcessMessage() {
  auto startTime = utils::Time::getInstance().getCurrentTime();
  notifyOK(startTime, kMachineStatusProcessingProduct);
  notifyProductTakenFromBuffer(startTime);

  if (checkBroken(startTime)) {
    // Broken
    notifyNOK(startTime, kMachineErrorCodeBroke);
    uint64_t repairtime = calculateRepairTime();
    notifyOK(startTime + repairtime, kMachineStatusConfiguring);
    notifyOK(startTime + repairtime + getInitializationDurationInMilliseconds(), kMachineStatusIdle);
  }
  else {
    // Not broken
    uint64_t timeSpendProcessing = startTime + currentConfig->getProcessTime();
    if (auto postProcess = getPostProcessInfo()) {
      if (momentOfLastItemProcessed + postProcess->getInputDelayInMillis() > timeSpendProcessing) {
        timeSpendProcessing = (momentOfLastItemProcessed + postProcess->getInputDelayInMillis());
      }
      notifyProductAddedToBuffer(timeSpendProcessing + postProcess->getPostProcessDurationInMillis());
    }
    else {
      notifyProductAddedToBuffer(timeSpendProcessing);
    }
    momentOfLastItemProcessed = timeSpendProcessing;
    notifyOK(timeSpendProcessing, kMachineStatusIdle);
  }
}

void SimulationMachineLocal::sendConfigureMessage(uint16_t configureId) {
  auto startTime = utils::Time::getInstance().getCurrentTime();
  notifyOK(startTime, kMachineStatusConfiguring);

  if (checkBroken(startTime)) {
    // Broken
    notifyNOK(startTime, kMachineErrorCodeBroke);
    uint64_t repairtime = calculateRepairTime();
    notifyOK(startTime + repairtime, kMachineStatusConfiguring);
    notifyOK(startTime + repairtime + getInitializationDurationInMilliseconds(), kMachineStatusIdle);
  }
  else {
    // Not broken
    notifyOK(startTime + getInitializationDurationInMilliseconds(), kMachineStatusIdle);
    currentConfig = getConfigurationById(configureId);
  }
}

void SimulationMachineLocal::setSimulationConnection(const network::ConnectionPtr &aConnection) {
  // don't need to set this
}

void SimulationMachineLocal::notifyRegisterMachine(uint64_t time) {
  auto notification = makeNotifcation(NotifyEventIds::eApplicationRegisterMachine);

  notification.setArgument(0, time);
  notification.setArgument(1, id);
  notification.setArgument(2, connection);

  notifyObservers(notification);
}

void SimulationMachineLocal::notifyMachineDisconnected(uint64_t time) {
  auto notification = makeNotifcation(NotifyEventIds::eApplicationMachineDisconnected);

  notification.setArgument(0, time);
  notification.setArgument(1, id);

  notifyObservers(notification);
}

void SimulationMachineLocal::notifyOK(uint64_t time, MachineStatus status) {
  auto notification = makeNotifcation(NotifyEventIds::eApplicationOK);

  notification.setArgument(0, time);
  notification.setArgument(1, id);
  notification.setArgument(2, status);

  notifyObservers(notification);
}

void SimulationMachineLocal::notifyNOK(uint64_t time, MachineErrorCode errorCode) {
  auto notification = makeNotifcation(NotifyEventIds::eApplicationNOK);

  notification.setArgument(0, time);
  notification.setArgument(1, id);
  notification.setArgument(2, errorCode);

  notifyObservers(notification);
}

void SimulationMachineLocal::notifyProductAddedToBuffer(uint64_t time) {
  auto notification = makeNotifcation(NotifyEventIds::eApplicationProductAddedToBuffer);

  notification.setArgument(0, time);
  notification.setArgument(1, id);

  notifyObservers(notification);
}

void SimulationMachineLocal::notifyProductTakenFromBuffer(uint64_t time) {
  auto notification = makeNotifcation(NotifyEventIds::eApplicationProductTakenFromBuffer);

  notification.setArgument(0, time);
  notification.setArgument(1, id);

  notifyObservers(notification);
}

bool SimulationMachineLocal::checkBroken(uint64_t currentTime) {
  if (currentTime < timeSinceBrokenCheck + checkCycle) {
    return false;
  }

  while (currentTime > timeSinceBrokenCheck) {
    // Catch up with history
    timeSinceBrokenCheck += checkCycle;
    uint64_t generated = utils::RandomHelper::getRandom(breakDistribution);
    if (generated == magicalNumber) {
      // It broke, set time since last check to now
      timeSinceBrokenCheck = currentTime;
      return true;
    }
  }
  return false;
}

uint64_t SimulationMachineLocal::calculateRepairTime() {
  return oneMinuteInMillis * utils::RandomHelper::getRandom(repairDistribution);
}

}
