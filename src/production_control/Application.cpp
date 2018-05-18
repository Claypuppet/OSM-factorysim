
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
  for (const auto &product : productionLine.getProducts()){
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

core::MachinePtr core::Application::getMachine(uint16_t machineId) {
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
      auto id = notification.getArgumentAsType<uint16_t >(0);
      auto event = std::make_shared<ApplicationStates::Event>(ApplicationStates::kEventTypeMachineStatusUpdate);
      event->setArgument(0, id);
      event->setArgument(1, core::Machine::MachineStatus::kMachineStatusIdle);
      scheduleEvent(event);
      break;
    }
    case NotifyEventIds::eApplicationStartInit:{
      auto id = notification.getArgumentAsType<uint16_t >(0);
      auto event = std::make_shared<ApplicationStates::Event>(ApplicationStates::kEventTypeMachineStatusUpdate);
      event->setArgument(0, id);
      event->setArgument(1, core::Machine::MachineStatus::kMachineStatusConfiguring);
      scheduleEvent(event);
      break;
    }
    case NotifyEventIds::eApplicationStartProcessing:{
      auto id = notification.getArgumentAsType<uint16_t >(0);
      auto event = std::make_shared<ApplicationStates::Event>(ApplicationStates::kEventTypeMachineStatusUpdate);
      event->setArgument(0, id);
      event->setArgument(1, core::Machine::MachineStatus::kMachineStatusProcessingProduct);
      scheduleEvent(event);
      break;
    }
    case NotifyEventIds::eApplicationDoneProcessing:{
      auto id = notification.getArgumentAsType<uint16_t >(0);
      auto event = std::make_shared<ApplicationStates::Event>(ApplicationStates::kEventTypeMachineStatusUpdate);
      event->setArgument(0, id);
      event->setArgument(1, core::Machine::MachineStatus::kMachineStatusIdle);
      scheduleEvent(event);
      break;
    }
    case NotifyEventIds::eApplicationOK:{
      auto id = notification.getArgumentAsType<uint16_t >(0);
      auto event = std::make_shared<ApplicationStates::Event>(ApplicationStates::kEventTypeMachineStatusUpdate);
      event->setArgument(0, id);
      event->setArgument(1, "OK");
      //scheduleEvent(event);
      break;
    }
    case NotifyEventIds::eApplicationNOK:{
      auto id = notification.getArgumentAsType<uint16_t >(0);
      auto event = std::make_shared<ApplicationStates::Event>(ApplicationStates::kEventTypeMachineStatusUpdate);
      event->setArgument(0, id);
      event->setArgument(1, "NOK");
      //scheduleEvent(event);
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

void core::Application::setProductionLine(const models::ProductionLine &executaionConfiguration) {
  productionLine = executaionConfiguration;
}

void core::Application::executeScheduler() {
  for (const auto &machine : machines) {
    if (machine->canDoAction(currentProduct)){
      machine->sendStartProcessMessage();
    }
  }
}

void core::Application::prepareScheduler() {
  // TODO: make this more dynamic. now sets product with id 1 (default tabled)
  changeProductionLineProduct(1);
}

void core::Application::changeProductionLineProduct(uint16_t productId) {
  currentProduct = productId;

  for (const auto &machine : machines){
    machine->sendConfigureMessage(productId);
  }
}

bool core::Application::setMachineStatus(uint16_t machineId, core::Machine::MachineStatus status) {
  auto machine = getMachine(machineId);
  if(machine){
    machine->setStatus(status);
    return true;
  }
  return false;
}
