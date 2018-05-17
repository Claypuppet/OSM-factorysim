
#include "AppConnectionHandler.h"

// other library includes
#include <network/Server.h>
#include <network/Client.h>

// project file includes
#include "states_application/BroadCastState.h"
#include "states_application/WaitForConnectionsState.h"
#include "NotificationTypes.h"

core::Application::~Application() {
  stopServer();
}

void core::Application::setMachines(const std::vector<MachinePtr>& aMachines) {
  // Set machines
  machines = aMachines;
  for (const auto &machine : machines) {
    machine->createInitialBuffers();
  }

  // Links all buffers for each production line
  for (const auto &product : executaionConfiguration.getProductionLineConfiguration().getProducts()){
    auto productId = product.getId();
    for (const auto &machine : machines){
      auto previousMachines = machine->getPreviousMachines(productId);
      if (previousMachines.empty()){
		continue;
      }
      for (const auto &previousMachine : previousMachines) {
        auto previousMachineObj = getMachine(previousMachine.getMachineId());
        if (!previousMachineObj){
          continue;
        }
        auto previousBuffer = previousMachineObj->getOutputBuffer(productId);
        machine->setInputBuffers(productId, previousBuffer);
      }
    }
  }
}

core::MachinePtr core::Application::getMachine(uint32_t machineId) {
  for (const auto &machine : machines) {
    if (machine->getId() == machineId) {
      return machine;
    }
  }
  return nullptr;
}

const std::vector<core::MachinePtr> &core::Application::getMachines() const {
  return machines;
}

void core::Application::setupNetwork() {
  if (server && server->isRunning()) {
    return;
  }

  AppConnectionHandler connectionHandler;
  handleNotificationsFor(connectionHandler);

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
  // TODO: move the case implementation to own method (or not?)
  switch(notification.getEventId()) {
    case NotifyEventIds::eApplicationRegisterMachine:{
      auto id = notification.getArgumentAsType<uint16_t>(0);
      auto connection = notification.getArgumentAsType<Network::ConnectionPtr>(1);

      auto event = std::make_shared<ApplicationStates::Event>(ApplicationStates::kEventTypeMachineRegistered);
      event->addArgument(id);
      event->addArgument(connection);
      scheduleEvent(event);
      break;
    }
    case NotifyEventIds::eApplicationMachineReady:{

      break;
    }
    case NotifyEventIds::eApplicationStartInit:{

      break;
    }
    case NotifyEventIds::eApplicationStartProcessing:{

      break;
    }
    case NotifyEventIds::eApplicationDoneProcessing:{

      break;
    }
    case NotifyEventIds::eApplicationOK:{

      break;
    }
    case NotifyEventIds::eApplicationNOK:{

      break;
    }
    default: {
      std::cerr << "unhandled notification with id " << notification.getEventId() << std::endl;
      break;
    }
  }

}

void core::Application::setStartState() {
  auto startState = std::make_shared<ApplicationStates::WaitForConnectionsState>(*this);
  setCurrentState(startState);
}

bool core::Application::allMachinesRegistered() {
  for (const auto &machine : machines){
    if (!machine->isConnected()){
      return false;
    }
  }
  return true;
}

void core::Application::registerMachine(uint16_t machineId, Network::ConnectionPtr connection) {
  auto machine = getMachine(machineId);
  if(machine){
    machine->setConnection(connection);

    if (allMachinesRegistered()) {
      auto event = std::make_shared<ApplicationStates::Event>(ApplicationStates::kEventTypeAllMachinesRegistered);
      scheduleEvent(event);
    }
  }
}

void core::Application::stopServer() {
  manager.stop();
  if(serverThread && serverThread->joinable())
  {
    serverThread->join();
  }
}

void core::Application::setExecutaionConfiguration(const models::Configuration &executaionConfiguration) {
  Application::executaionConfiguration = executaionConfiguration;
}

void core::Application::executeScheduler() {

}
