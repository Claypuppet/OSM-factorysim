//
// Created by don on 20-4-18.
//

#include <cereal/archives/portable_binary.hpp>
#include <network/Protocol.h>
#include <utils/time/Time.h>
#include "SimulationMachine.h"

namespace simulation {

SimulationMachine::SimulationMachine(const models::Machine &aMachine) :
	core::Machine(aMachine), simConnection(nullptr), ready(false), awaitingSimulationResponse(false) {
}

SimulationMachine::SimulationMachine(const SimulationMachine &aMachine) :
	core::Machine(aMachine), simConnection(nullptr), ready(false), awaitingSimulationResponse(false) {
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
  models::Machine machineInfo = static_cast<models::Machine>(*this);
  message.setBodyObject<models::Machine>(machineInfo);
  sendSimulationMessage(message);
}

void SimulationMachine::sendTurnOnCommand() {
  network::Message message(network::Protocol::kSimMessageTypeTurnOn);
  sendSimulationMessage(message);
}

void SimulationMachine::sendTurnOffCommand() {
  network::Message message(network::Protocol::kSimMessageTypeTurnOff);
  sendSimulationMessage(message);
}

bool SimulationMachine::isReadyForSimulation() const {
  return isSimulationConnected() && ready;
}

void SimulationMachine::setReady(bool aReady) {
  SimulationMachine::ready = true;
}

uint64_t SimulationMachine::getNextEventMoment() {
  if (!simulationEvents.empty()){
    const auto& event = simulationEvents.front();
    return event.getArgumentAsType<uint64_t>(0);
  }
  return 0;
}

std::vector<patterns::notifyobserver::NotifyEvent> SimulationMachine::getEvents(uint64_t moment) {
  std::vector<patterns::notifyobserver::NotifyEvent> list;
  while(!simulationEvents.empty() && simulationEvents.front().getArgumentAsType<uint64_t>(0) == moment){
    list.emplace_back(simulationEvents.front());
    simulationEvents.pop();
  }
  return list;
}

void SimulationMachine::addEvent(const patterns::notifyobserver::NotifyEvent &simulationEvent) {
  simulationEvents.emplace(simulationEvent);
  awaitingSimulationResponse = false;
}

void SimulationMachine::sendMessage(network::Message &message) {
  Machine::sendMessage(message);
  awaitingSimulationResponse = true;
}

bool SimulationMachine::isWaitingForResponse() const {
  return Machine::isWaitingForResponse() && awaitingSimulationResponse;
}

} // simulation

