
#include "AppConnectionHandler.h"

// other library includes
#include <network/Server.h>
#include <network/Client.h>

// project file includes
#include "states_application/BroadCastState.h"

void core::Application::addMachine(const Machine &aMachine) {
  machines.push_back(aMachine);
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

void core::Application::handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) {

}

void core::Application::setStartState() {
  auto startState = std::make_shared<ApplicationStates::BroadCastState>(*this);
  setCurrentState(startState);
}