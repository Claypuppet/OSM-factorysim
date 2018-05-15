
#include "AppConnectionHandler.h"

// other library includes
#include <network/Server.h>
#include <network/Client.h>

// project file includes
#include "states_application/BroadCastState.h"
#include "SimulationController.h"

void core::Application::setMachines(const std::vector<simulation::SimulationMachinePtr>& simulationMachines) {
  for (const simulation::SimulationMachinePtr& simulationMachine : simulationMachines) {
    core::Machine machine = (core::Machine) (*simulationMachine);
    machines.push_back(machine);
  }
}

core::MachinePtr core::Application::getMachine(uint16_t machineId) {
  for (Machine &machine : machines) {
    if (machine.getId()==machineId) {
      return std::make_shared<Machine>(machine);
    }
  }
  return nullptr;
}

void core::Application::setupNetwork() {
  if (server && server->isRunning()) {
    return;
  }

  AppConnectionHandler connectionHandler;
//	handleNotificationsFor(connectionHandler);

  serverThread = manager.runServiceThread();
  server = manager.createServer(std::make_shared<AppConnectionHandler>(connectionHandler), 50);
  server->start();
}

void core::Application::joinServerThread() {
  serverThread->join();
}

void core::Application::startServer() {
  if (!isServerRunning()) {
    server->start();
  }
}

bool core::Application::isServerRunning() {
  return server->isRunning();
}

Network::ServerPtr core::Application::getServer() {
  return Network::ServerPtr();
}

void core::Application::handleNotification(const patterns::NotifyObserver::NotifyEvent &notification) {

}

void core::Application::setStartState() {
  auto startState = std::make_shared<ApplicationStates::BroadCastState>(*this);
  setCurrentState(startState);
}

bool core::Application::allMachinesRegistered() {
  for (const auto &machine : machines){
    if (!machine.isConnected()){
      return false;
    }
  }
  return true;
}

void core::Application::registerMachine(uint16_t machineId, Network::ConnectionPtr connection) {
  auto machine = getMachine(machineId);
  if(machine){
    machine->setConnection(connection);
  }
}