//
// Created by hqnders on 20/04/18.
//

#include <models/Machine.h>
#include "Application.h"
#include "states_production/ConnectState.h"
#include "states_production/Inititalization/ConfigureState.h"

namespace machinecore {

Application::Application(uint16_t aMachineId)
    : patterns::statemachine::Context(),
      id(aMachineId),
      connectionHandler(),
      machine(),
      newConfigId(0),
      currentConfig(0) {

}

Application::~Application() {
  stop();
}

void Application::handleNotification(const patterns::NotifyObserver::NotifyEvent &notification) {
  switch (notification.getEventId()) {
    case NotifyEventType::kNotifyEventTypeServiceStarted: {
      auto event = std::make_shared<productionstates::Event>(productionstates::EventType::kEventTypeConnected);
      scheduleEvent(event);
      break;
    }

    case NotifyEventType::kNotifyEventTypeServiceError : {

      break;
    }

    case NotifyEventType::kNotifyEventTypeMachineConfigReceived : {
      auto event = std::make_shared<productionstates::Event>(productionstates::EventType::kEventTypeReceivedConfig);
      event->setArgument(notification.getArgument(0));
      scheduleEvent(event);
      break;
    }

    case NotifyEventType::kNotifyEventTypeStartProcess: {
      auto event = std::make_shared<productionstates::Event>(productionstates::EventType::kEventTypeProcessProduct);
      scheduleEvent(event);
      break;
    }

    default:break;
  }
}

void Application::setStartState() {
  setCurrentState(std::make_shared<productionstates::ConnectState>(*this));
}

void Application::stop() {
  // Stop the manager
  manager.stop();

  // Join the client thread
  if (clientThread && clientThread->joinable()) {
    clientThread->join();
  }
}

void Application::setupNetwork() {
  clientThread = manager.runServiceThread();

  handleNotificationsFor(connectionHandler);

  client = manager.createClient(std::shared_ptr<Communication::NetworkComponent>(&connectionHandler));

  auto eventDispatcherPtr = std::make_shared<NetworkEventDispatcher>();
  client->setServiceEventListener(eventDispatcherPtr);
  handleNotificationsFor(*eventDispatcherPtr);

  client->start();
}

const models::MachineConfiguration &Application::getCurrentConfig() const {
  return configurations.at(currentConfig);
}

void Application::setCurrentConfig() {
  for (auto &configuration : configurations) {
    if (configuration.getProductId() == newConfigId) {
      currentConfig = newConfigId;
      auto event = std::make_shared<productionstates::Event>(productionstates::EventType::kEventTypeConfigured);
      scheduleEvent(event);
    }
  }
}

void Application::registerMachine() {
  connectionHandler.sendRegisterMachineMessage(id);
}

bool Application::setCurrentConfigId(uint32_t configID) {

  for (auto &configuration : configurations) {
    if (configuration.getProductId() == configID) {
      newConfigId = configID;
      auto event = std::make_shared<productionstates::Event>(productionstates::EventType::kEventTypeConfigured);
      scheduleEvent(event);
      return true;
    }
  } // access by reference to avoid copying
  return false;
}

uint32_t Application::getCurrentConfigId() const {
  return newConfigId;
}

void Application::takeProductIn() {
  auto event = std::make_shared<productionstates::Event>(productionstates::EventType::kEventTypeProcessProduct);
  scheduleEvent(event);
}

void Application::processProduct() {
  auto event = std::make_shared<productionstates::Event>(productionstates::EventType::kEventTypeFinishedProduct);
  scheduleEvent(event);
}


void Application::takeProductOut() {
  auto event = std::make_shared<productionstates::Event>(productionstates::EventType::kEventTypeProductTakenOut);
  scheduleEvent(event);
}

} // namespace machinecore
