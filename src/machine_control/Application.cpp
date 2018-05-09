//
// Created by hqnders on 20/04/18.
//

#include "Application.h"
#include "states_production/ConnectState.h"
#include "states_production/Inititalization/ConfigureState.h"

namespace MachineCore {
Application::Application(const Models::Machine &aMachineInfo)
    : Patterns::Statemachine::Context(), machineInfo(aMachineInfo) {
}

void Application::handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) {
  switch (notification.getEventId()) {
    case NotifyEventType::kNotifyEventTypeServiceStarted: {
      auto e = std::make_shared<ProductionStates::Event>(ProductionStates::EventType::kEventTypeConnected);
      scheduleEvent(e);
      break;
    }

    case NotifyEventType::kNotifyEventTypeServiceError : {
      break;
    }

    default:break;
  }
}

const Models::Machine &Application::getMachineInfo() const {
  return machineInfo;
}

void Application::setMachineInfo(const Models::Machine &machineInfo) {
  Application::machineInfo = machineInfo;
}

void Application::setStartState() {
  setCurrentState(std::make_shared<ProductionStates::ConnectState>(*this));
}

void Application::setupNetwork() {
  clientThread = manager.runServiceThread();

  Communication::NetworkComponent connectionHandler;
  handleNotificationsFor(connectionHandler);

  std::cout << "application has connection";
  client = manager.createClient(std::make_shared<Communication::NetworkComponent>(connectionHandler));

  auto eventDispatcherPtr = std::make_shared<NetworkEventDispatcher>();
  client->setServiceEventListener(eventDispatcherPtr);
  handleNotificationsFor(*eventDispatcherPtr);

  client->start();
}

}
