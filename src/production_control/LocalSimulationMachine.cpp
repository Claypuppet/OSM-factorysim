//
// Created by klei on 6/6/18.
//

#include "LocalSimulationMachine.h"
namespace simulation {

LocalSimulationMachine::LocalSimulationMachine(const models::Machine &aMachine) : SimulationMachine(aMachine), remoteMachine(aMachine) {
}

bool LocalSimulationMachine::isConnected() const {
  return Machine::isConnected();
}

void LocalSimulationMachine::setConnection(const network::ConnectionPtr &aConnection) {
  Machine::setConnection(aConnection);
}

bool LocalSimulationMachine::isSimulationConnected() const {
  return SimulationMachine::isSimulationConnected();
}

bool LocalSimulationMachine::isReadyForSimulation() const {
  return SimulationMachine::isReadyForSimulation();
}

void LocalSimulationMachine::sendMessage(network::Message &message) {
  Machine::sendMessage(message);
}

}
