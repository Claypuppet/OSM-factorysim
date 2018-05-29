
#include "ConnectionHandler.h"

// other library includes
#include <network/Server.h>
#include <network/Client.h>

// project file includes
#include "states_application/BroadCastState.h"
#include "states_application/WaitForConnectionsState.h"
#include "NotificationTypes.h"

core::Application::Application() {
}

core::Application::~Application() {
  stopServer();
}

void core::Application::setMachines(const std::vector<MachinePtr> &aMachines) {
  // Set machines
  machines = aMachines;
  for (const auto &machine : machines) {
    machine->createInitialBuffers();
  }

  // Links all buffers for each production line
  for (const std::shared_ptr<models::Product> product : productionLine->getProducts()) {
    auto productId = product->getId();

    for (const auto &machine : machines) {
      auto previousMachines = machine->getPreviousMachines(productId);
      if (previousMachines.empty()) {
        throw std::runtime_error("machine can not have empty previous machines");
      }
      for (const auto &previousMachine : previousMachines) {
        auto previousMachineObj = getMachine(previousMachine->getMachineId());
        if (!previousMachineObj) {
          continue;
        }
        auto previousBuffer = previousMachineObj->getOutputBuffer(productId);
        machine->addInputBuffer(productId, previousBuffer);
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
  communication::ConnectionHandler connectionHandler;
  handleNotificationsFor(connectionHandler);

  serverThread = manager.runServiceThread();
  server = manager.createServer(std::make_shared<communication::ConnectionHandler>(connectionHandler), 50);
  server->start();
}
void core::Application::handleNotification(const patterns::notifyobserver::NotifyEvent &notification) {
  // TODO: move the case implementation to own method (or not?)
  switch (notification.getEventId()) {
    case NotifyEventIds::eApplicationRegisterMachine: {
      auto time = notification.getArgumentAsType<uint64_t>(0);
      auto id = notification.getArgumentAsType<uint16_t>(1);
      auto connection = notification.getArgumentAsType<network::ConnectionPtr>(2);

      auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeMachineRegistered);
      event->addArgument(id);
      event->addArgument(connection);
      scheduleEvent(event);
      break;
    }
    case NotifyEventIds::eApplicationOK: {
      auto time = notification.getArgumentAsType<uint64_t>(0);
      auto id = notification.getArgumentAsType<uint16_t>(1);
      auto status = notification.getArgumentAsType<models::Machine::MachineStatus>(2);
      auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeMachineStatusUpdate);
      event->setArgument(0, id);
      event->setArgument(1, status);
      scheduleEvent(event);
      break;
    }
    case NotifyEventIds::eApplicationNOK: {
      auto time = notification.getArgumentAsType<uint64_t>(0);
      auto id = notification.getArgumentAsType<uint16_t>(1);
      auto errorCode = notification.getArgumentAsType<uint16_t>(2);
      auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeMachineStatusUpdate);
      event->setArgument(0, id);
      event->setArgument(1, errorCode);
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
  auto startState = std::make_shared<applicationstates::WaitForConnectionsState>(*this);
  setCurrentState(startState);
}

bool core::Application::allMachinesRegistered() {
  for (const auto &machine : machines) {
    if (!machine->isConnected()) {
      return false;
    }
  }
  return true;
}

void core::Application::registerMachine(uint16_t machineId, network::ConnectionPtr connection) {
  auto machine = getMachine(machineId);
  if (machine) {
    machine->setConnection(connection);

    if (allMachinesRegistered()) {
      auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeAllMachinesRegistered);
      scheduleEvent(event);
    }
  }
}

void core::Application::stopServer() {
  manager.stop();
  if (serverThread && serverThread->joinable()) {
    serverThread->join();
  }
}

void core::Application::setProductionLine(const models::ProductionLine &productionLine) {
  this->productionLine = std::make_shared<models::ProductionLine>(productionLine);
}

void core::Application::setProductionLine(const std::shared_ptr<models::ProductionLine> &productionLine) {
  this->productionLine = productionLine;
}

void core::Application::executeScheduler() {
  for (const auto &machine : machines) {
    if (machine->canDoAction()) {
      machine->sendStartProcessMessage();
    }
  }
}

void core::Application::prepareScheduler() {
  // TODO: make this more dynamic. now sets product with id 1 (default tables)
  uint16_t configId = 0;
  if (!productionLine->getProducts().empty()) {
    configId = productionLine->getProducts().front()->getId();
  }
  changeProductionLineProduct(configId);
}

void core::Application::changeProductionLineProduct(uint16_t productId) {
  currentProduct = productId;

  for (const auto &machine : machines) {
    machine->sendConfigureMessage(productId);
  }
}

bool core::Application::setMachineStatus(uint16_t machineId, core::Machine::MachineStatus status) {
  auto machine = getMachine(machineId);
  if (machine) {
    machine->setStatus(status);
    return true;
  }
  return false;
}
