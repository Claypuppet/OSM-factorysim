//
// Created by hqnders on 20/04/18.
//

#include <models/Machine.h>
#include "Application.h"
#include "states_production/ConnectState.h"
#include "states_production/Inititalization/ConfigureState.h"

namespace machinecore {

Application::Application(uint16_t aMachineId)
    : patterns::statemachine::Context(), id(aMachineId), machine() {
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

  client = manager.createClient(std::make_shared<Communication::NetworkComponent>(connectionHandler));

  auto eventDispatcherPtr = std::make_shared<NetworkEventDispatcher>();
  client->setServiceEventListener(eventDispatcherPtr);
  handleNotificationsFor(*eventDispatcherPtr);

  client->start();
}
void Application::registerMachine() {
  connectionHandler.sendRegisterMachineMessage(getId());
}

} // namespace machinecore
