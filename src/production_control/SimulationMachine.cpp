//
// Created by don on 20-4-18.
//

#include <cereal/archives/portable_binary.hpp>
#include <network/Protocol.h>
#include <utils/time/Time.h>

#include "SimulationMachine.h"
#include "NotificationTypes.h"

namespace simulation {

SimulationMachine::SimulationMachine(const models::Machine &aMachine) :
    core::Machine(aMachine),
    eventPusher(),
    ready(false),
    simConnection(),
    awaitingSimulationResponse(false),
    simulationStatusEvents(),
    simulationBufferEvents() {
}

bool SimulationMachine::isSimulationConnected() const {
  return !!simConnection;
}

void SimulationMachine::sendSimulationMessage(network::Message &message) {
  message.setTime(utils::Time::getInstance().getCurrentTime());
  if (isSimulationConnected()) {
    simConnection->writeMessage(message);
  }
}

void SimulationMachine::setSimulationConnection(const network::ConnectionPtr &aConnection) {
  simConnection = aConnection;
}

void SimulationMachine::sendSimulationConfiguration() {
  network::Message message(network::Protocol::kSimMessageTypeConfig);
  auto machineInfo = std::make_shared<models::Machine>(*this);
  message.setBodyObject<models::MachinePtr>(machineInfo);
  sendSimulationMessage(message);
}

void SimulationMachine::sendTurnOnCommand() {
  network::Message message(network::Protocol::kSimMessageTypeTurnOn);
  sendSimulationMessage(message);
  awaitingSimulationResponse = false;
}

void SimulationMachine::sendTurnOffCommand() {
  network::Message message(network::Protocol::kSimMessageTypeTurnOff);
  sendSimulationMessage(message);
  setStatus(kMachineStatusDisconnected);
  awaitingSimulationResponse = false;
}

bool SimulationMachine::isReadyForSimulation() const {
  return isSimulationConnected() && ready;
}

void SimulationMachine::setReady(bool aReady) {
  SimulationMachine::ready = true;
}

uint64_t SimulationMachine::getNextEventMoment() {
  uint64_t lowest = 0;
  if (!simulationStatusEvents.empty()) {
    const auto &event = simulationStatusEvents.front();
    lowest = event.getArgumentAsType<uint64_t>(0);
  }
  if (!simulationBufferEvents.empty()) {
    const auto &event = simulationBufferEvents.front();
    auto lowestBufferEvent = event.getArgumentAsType<uint64_t>(0);
    if (lowest == 0 || lowest > lowestBufferEvent) {
      lowest = lowestBufferEvent;
    }
  }
  return lowest;
}

void SimulationMachine::getEvents(uint64_t moment, std::vector<patterns::notifyobserver::NotifyEvent> &list) {
  while (!simulationBufferEvents.empty() && simulationBufferEvents.front().getArgumentAsType<uint64_t>(0) == moment) {
    list.emplace_back(simulationBufferEvents.front());
    simulationBufferEvents.pop();
  }
  while (!simulationStatusEvents.empty() && simulationStatusEvents.front().getArgumentAsType<uint64_t>(0) == moment) {
    list.emplace_back(simulationStatusEvents.front());
    simulationStatusEvents.pop();
  }
}

void SimulationMachine::addEvent(const patterns::notifyobserver::NotifyEvent &simulationEvent) {
  std::lock_guard<std::mutex> guard(eventPusher);
  switch (simulationEvent.getEventId()) {
    case NotifyEventIds::eApplicationOK:
      // OK checks if the state is idle,
      if (simulationEvent.getArgumentAsType<models::Machine::MachineStatus>(2) == kMachineStatusIdle) {
        awaitingSimulationResponse = false;
      }
    case NotifyEventIds::eApplicationProductTakenFromBuffer:
    case NotifyEventIds::eApplicationNOK:
      simulationStatusEvents.emplace(simulationEvent);
      break;
    case NotifyEventIds::eApplicationProductAddedToBuffer:
      simulationBufferEvents.emplace(simulationEvent);
      break;
    default:
      break;
  }
}

void SimulationMachine::sendMessage(network::Message &message) {
  awaitingSimulationResponse = true;
  Machine::sendMessage(message);
}

bool SimulationMachine::isWaitingForSimulationResponse() const {
  return awaitingSimulationResponse;
}

bool SimulationMachine::isWaitingForResponse() {
  std::lock_guard<std::mutex> guard(eventPusher);
  return Machine::isWaitingForResponse() && awaitingSimulationResponse;
}

void SimulationMachine::handleBreak() {
  Machine::handleBreak();
  // Machine broke, so clear all buffer events
  std::queue<patterns::notifyobserver::NotifyEvent> empty;
  std::swap(simulationBufferEvents, empty);
}

bool SimulationMachine::isIdle(bool completelyIdle) {
  return simulationBufferEvents.empty() && simulationStatusEvents.empty() && Machine::isIdle(completelyIdle);
}

} // simulation

