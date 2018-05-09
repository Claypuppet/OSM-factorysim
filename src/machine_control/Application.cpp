//
// Created by hqnders on 20/04/18.
//

#include "Application.h"
#include "states_production/ConnectState.h"

namespace machinecore {

Application::Application(uint16_t aMachineId, Machine aMachine)
    : Patterns::Statemachine::Context(), id(aMachineId), machine(aMachine) {

  clientThread = manager.runServiceThread();

  Communication::NetworkComponent connectionHandler;
  handleNotificationsFor(connectionHandler);

  client = manager.createClient(std::make_shared<Communication::NetworkComponent>(connectionHandler));

  setCurrentState(std::make_shared<ProductionStates::ConnectState>(*this));
}

Application::~Application() {
  stop();
}

void Application::handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) {
}

void Application::setStartState() {
  setCurrentState(std::make_shared<ProductionStates::ConnectState>(*this));
}

void Application::stop() {
  // Stop the manager
  manager.stop();

  // Join the client thread
  if (clientThread->joinable()) {
    clientThread->join();
  }
}
} // namespace machinecore
