
#include "ConnectionHandler.h"

// other library includes
#include <network/Server.h>
#include <network/Client.h>
#include <utils/time/Time.h>
#include <utils/Logger.h>

// project file includes
#include "states_application/BroadCastState.h"
#include "states_application/WaitForConnectionsState.h"
#include "NotificationTypes.h"

core::Application::~Application() {
  stopServer();
}

void core::Application::setMachines(const std::vector<MachinePtr> &aMachines) {
  // Set machines
  firstMachinesInLine.clear();
  lastMachineInLine.clear();
  machines = aMachines;
  for (const auto &machine : machines) {
    machine->createInitialBuffers();
  }

  // Links all buffers (for each product type in production line)
  for (const std::shared_ptr<models::Product> &product : productionLine->getProducts()) {
    auto productId = product->getId();
    for (const auto &machine : machines) {
      if (!machine->hasConfiguration(productId)){
        // Machine doesn't have a configuration for this product.
        continue;
      }
      for (const auto &previousMachine : machine->getPreviousMachines(productId)) {
        if (auto previousMachineObj = getMachine(previousMachine->getMachineId())) {
          auto previousBuffer = previousMachineObj->getOutputBuffer(productId);
          machine->addInputBuffer(productId, previousBuffer);
        }
        else{
          // This machine is the first in line because it doesnt have a previous machine
          firstMachinesInLine[productId].emplace_back(machine);
        }
      }
      if(machine->isLastInLine(productId)){
        // This machine is last in line
        lastMachineInLine[productId] = machine;
      }
    }
  }
  std::stringstream stream;
  for(const auto &machineList : firstMachinesInLine){
    stream << std::endl << "Machines for product: " << productionLine->getProductById(machineList.first)->getName() << std::endl;
    for(const auto &machine : machineList.second){
      for(const auto &input : machine->getInputBuffers(machineList.first)){
        input->debugPrintBuffersChain(stream);
      }
    }
  }
  stream << std::endl;
  utils::Logger::log(stream.str());
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
      onHandleRegisterNotification(id, connection);
      break;
    }

    case NotifyEventIds::eApplicationOK: {
      auto time = notification.getArgumentAsType<uint64_t>(0);
      auto id = notification.getArgumentAsType<uint16_t>(1);
      auto status = notification.getArgumentAsType<models::Machine::MachineStatus>(2);
      onHandleOKNotification(id, status);
      break;
    }

    case NotifyEventIds::eApplicationNOK: {
      auto time = notification.getArgumentAsType<uint64_t>(0);
      auto id = notification.getArgumentAsType<uint16_t>(1);
      auto errorCode = notification.getArgumentAsType<models::Machine::MachineErrorCode>(2);
      onHandleNOKNotification(id, errorCode);
      break;
    }

    default: {
      std::cerr << "unhandled notification with id " << notification.getEventId() << std::endl;
      break;
    }
  }
}

void core::Application::onHandleRegisterNotification(uint16_t id, const network::ConnectionPtr &connection){

  auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeMachineRegistered);
  event->addArgument(id);
  event->addArgument(connection);
  scheduleEvent(event);
}


void core::Application::onHandleOKNotification(uint16_t id, models::Machine::MachineStatus status){
  auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeMachineStatusUpdate);
  event->setArgument(0, id);
  event->setArgument(1, status);
  scheduleEvent(event);
}


void core::Application::onHandleNOKNotification(uint16_t id, models::Machine::MachineErrorCode errorCode){
  switch(errorCode){
    case models::Machine::MachineErrorCode::kMachineErrorCodeBroke : {
      auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeMachineStatusUpdate);
      event->setArgument(0, id);
      event->setArgument(1, models::Machine::kMachineStatusBroken);
      scheduleEvent(event);
      break;
    }
    default : {
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

void core::Application::setProductionLine(const models::ProductionLinePtr &productionLine) {
  this->productionLine = productionLine;
}

void core::Application::executeScheduler() {
  tryChangeProduction();
  for (const auto &machine : machines) {
    machine->doNextAction();
  }
}

void core::Application::prepareScheduler() {
  // TODO: make this more dynamic. now sets product with id 1 (default tables)
  uint16_t configId = 0;
  if (productionLine && !productionLine->getProducts().empty()) {
    configId = productionLine->getProducts().front()->getId();
  }
  changeProductionLineProduct(configId);
}

void core::Application::changeProductionLineProduct(uint16_t productId) {
  for (const auto &machine : machines) {
    machine->prepareReconfigure(productId, currentProductId == 0);
  }
  currentProductId = productId;
  momentStartingCurrentProduct = utils::Time::getInstance().getCurrentTime();
}

bool core::Application::setMachineStatus(uint16_t machineId, core::Machine::MachineStatus status) {
  auto machine = getMachine(machineId);
  if (machine) {
    machine->setStatus(status);
    return true;
  }
  return false;
}

void core::Application::tryChangeProduction() {
  // Temp wait at least 4 hours
  static uint64_t fourHoursInMillis = 14400000;
  if(utils::Time::getInstance().getCurrentTime() < momentStartingCurrentProduct + fourHoursInMillis){
    return;
  }
  // Temp switch to next product which is not current product
  for(auto &product : productionLine->getProducts()){
    if(currentProductId != product->getId()){
      changeProductionLineProduct(product->getId());
      break;
    }
  }
}
