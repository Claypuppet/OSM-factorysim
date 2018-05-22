//
// Created by don on 20-4-18.
//

#include <cereal/archives/portable_binary.hpp>
#include <network/Protocol.h>
#include "SimulationMachine.h"

namespace simulation {

SimulationMachine::SimulationMachine(const models::Machine &aMachine) :
	core::Machine(aMachine), simConnection(nullptr), ready(false) {
}

SimulationMachine::SimulationMachine(const SimulationMachine &aMachine) :
	core::Machine(aMachine), simConnection(nullptr), ready(false) {
}

SimulationMachine &SimulationMachine::operator=(const SimulationMachine &rhs) {
  if (this != &rhs) {
	core::Machine::operator=(rhs);
	simConnection = rhs.simConnection;
  }
  return *this;
}

bool SimulationMachine::isSimulationConnected() const {
  return !!simConnection;
}

void SimulationMachine::sendSimulationMessage(network::Message &message) {
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
} // simulation

