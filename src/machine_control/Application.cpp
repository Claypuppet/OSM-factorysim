//
// Created by hqnders on 20/04/18.
//

#include <models/Machine.h>
#include <utils/CommandLineArguments.h>
#include "Application.h"
#include "states_application/ConnectState.h"
#include "states_machine/MachineState.h"

namespace machinecore {

Application::Application(uint16_t aMachineId)
    : patterns::statemachine::Context(),
      id(aMachineId),
      configToSet(0) {
  connectionHandler = std::make_shared<Communication::NetworkComponent>();
}

Application::~Application() {
  stop();
}

void Application::handleNotification(const patterns::notifyobserver::NotifyEvent &notification) {
  switch (notification.getEventId()) {
    case kNotifyEventTypeServiceStarted: {
      auto event = std::make_shared<applicationstates::Event>(applicationstates::EventType::kEventTypeConnected);
      scheduleEvent(event);
      break;
    }

    case kNotifyEventTypeServiceError : {
      break;
    }

    case kNotifyEventTypeStartProcess: {
      auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeProcessProduct);
      scheduleEvent(event);
      break;
    }

    case kNotifyEventTypeMachineFinishedProcess: {
      auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeFinishedProcessing);
      scheduleEvent(event);
      break;
    }

    case kNotifyEventTypeConfigure: {
      auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeReconfigure);
      event->addArgument<uint16_t>(notification.getFirstArgumentAsType<uint16_t>());
      scheduleEvent(event);
      break;
    }

    case kNotifyEventTypeMachineConfigured: {
      auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeConfigured);
      scheduleEvent(event);
      break;
    }

    case kNotifyEventTypeMachineFailedToConfigure: {
      auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeFailedToConfigure);
      scheduleEvent(event);
      break;
    }

    case kNotifyEventTypeMachineBroke: {
      auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeMachineBroke);
      scheduleEvent(event);
      break;
    }

    default: break;
  }
}

void Application::setStartState() {
  setCurrentState(std::make_shared<applicationstates::ConnectState>(*this));
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

  // Because someone forgot to implement the find PC in the application, hardcoded here
  const auto &pcip = utils::CommandLineArguments::getInstance().getKwarg("-pcip");
  if (!pcip) {
    manager.setRemoteHost(pcip.value);
  } else {
    manager.setRemoteHost("localhost");
  }

  client = manager.createClient(connectionHandler);

  auto eventDispatcherPtr = std::make_shared<NetworkEventDispatcher>();
  client->setServiceEventListener(eventDispatcherPtr);
  handleNotificationsFor(*eventDispatcherPtr);

  client->start();
}

void Application::registerMachine() {
  connectionHandler->sendRegisterMachineMessage(id);
}

void Application::statusUpdate(models::Machine::MachineStatus status) {
  connectionHandler->sendStatusUpdate(status);
}

void Application::machineBroke(){
  connectionHandler->sendResponseNOK(models::Machine::kMachineErrorCodeBroke);
}

} // machinecore
