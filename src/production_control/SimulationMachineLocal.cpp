//
// Created by klei on 6/11/18.
//

#include <utils/time/Time.h>
#include "SimulationMachineLocal.h"
#include "NotificationTypes.h"

namespace simulation {

SimulationMachineLocal::SimulationMachineLocal(const models::Machine &aMachine)
    : SimulationMachine(aMachine), connected(false) {
}

bool SimulationMachineLocal::isSimulationConnected() const {
  return true;
}

bool SimulationMachineLocal::isReadyForSimulation() const {
  return true;
}

void SimulationMachineLocal::sendTurnOnCommand() {
  notifyRegisterMachine(utils::Time::getInstance().getCurrentTime());
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
}

void SimulationMachineLocal::sendStartProcessMessage() {
  auto startTime = utils::Time::getInstance().getCurrentTime();
  notifyOK(startTime, kMachineStatusProcessingProduct);
  notifyProductTakenFromBuffer(startTime);
  notifyProductAddedToBuffer(startTime + currentConfig->getProcessTime());
  notifyOK(startTime + currentConfig->getProcessTime(), kMachineStatusIdle);

  // TODO: notify app -> state processing
  // TODO: notify app -> taken product from buffer
  // TODO: check broken ?

  // Broken
  // TODO: notify app -> error broke
  // TODO: notify app -> state configuring
  // TODO: notify app -> state idle

  // Not borken
  // TODO: notify app -> product to buffer
  // TODO: notify app -> state idle
}

void SimulationMachineLocal::sendConfigureMessage(uint16_t configureId) {
  auto startTime = utils::Time::getInstance().getCurrentTime();
  notifyOK(startTime, kMachineStatusConfiguring);
  notifyOK(startTime, kMachineStatusIdle);
  currentConfig = getConfigurationById(configureId);
  // TODO: notify app -> configuring
  // TODO: check broken ?

  // Broken
  // TODO: notify app -> error broke
  // TODO: notify app -> state configuring
  // TODO: notify app -> state idle

  // Not broken
  // TODO: notify app -> state idle
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

}
