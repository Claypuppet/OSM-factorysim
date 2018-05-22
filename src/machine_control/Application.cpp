//
// Created by hqnders on 20/04/18.
//

#include <models/Machine.h>
#include "Application.h"
#include "states_application/ConnectState.h"
#include "states_application/Inititalization/ConfigureState.h"

namespace machinecore {

Application::Application(uint16_t aMachineId)
	: patterns::statemachine::Context(),
	  id(aMachineId),
	  nextConfigId(0),
	  currentConfigId(0),
	  configurations() {
  connectionHandler = std::make_shared<Communication::NetworkComponent>();
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
	  event->setArgument<uint16_t>(notification.getArgumentAsType<uint16_t>(0));
	  scheduleEvent(event);
	  break;
	}

	case NotifyEventType::kNotifyEventTypeStartProcess: {
	  auto event = std::make_shared<productionstates::Event>(productionstates::EventType::kEventTypeTakeProduct);
	  scheduleEvent(event);
	  break;
	}

	default:
	  break;
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

  handleNotificationsFor(*connectionHandler);

  client = manager.createClient(connectionHandler);

  auto eventDispatcherPtr = std::make_shared<NetworkEventDispatcher>();
  client->setServiceEventListener(eventDispatcherPtr);
  handleNotificationsFor(*eventDispatcherPtr);

  client->start();
}

const models::MachineConfiguration &Application::getCurrentConfig() const {
  return configurations.at(currentConfigId);
}

void Application::setCurrentConfig() {
  for (auto &configuration : configurations) {
	if (configuration.getProductId() == nextConfigId) {
	  currentConfigId = nextConfigId;
	  auto event = std::make_shared<productionstates::Event>(productionstates::EventType::kEventTypeConfigured);
	  scheduleEvent(event);
	}
  }
}

void Application::registerMachine() {
  connectionHandler->sendRegisterMachineMessage(id);
}

bool Application::setCurrentConfigId(uint32_t configID) {

  for (auto &configuration : configurations) {
	if (configuration.getProductId() == configID) {
	  nextConfigId = configID;
	  auto event = std::make_shared<productionstates::Event>(productionstates::EventType::kEventTypeConfigured);
	  scheduleEvent(event);
	  return true;
	}
  } // access by reference to avoid copying
  return false;
}

uint32_t Application::getCurrentConfigId() const {
  return currentConfigId;
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

void Application::statusUpdate(models::Machine::MachineStatus status) {
  connectionHandler->sendStatusUpdate(status);
}
} // namespace machinecore
