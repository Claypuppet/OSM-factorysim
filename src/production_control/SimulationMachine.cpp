//
// Created by don on 20-4-18.
//

#include <cereal/archives/portable_binary.hpp>
#include <network/Protocol.h>
#include <utils/time/Time.h>
#include "SimulationMachine.h"

namespace simulation {

SimulationMachine::SimulationMachine(const models::Machine &aMachine) :
	core::Machine(aMachine), eventPusher(), ready(false), simConnection(), awaitingSimulationResponse(false), simulationEvents() {
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
  std::lock_guard<std::mutex> guard(eventPusher);
  simulationEvents.emplace(simulationEvent);
  try{
    if(simulationEvent.getArgumentAsType<models::Machine::MachineStatus>(2) == kMachineStatusIdle){
      awaitingSimulationResponse = false;
    }
  }
  catch (const std::exception &e){
    // temp because derp
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

} // simulation

