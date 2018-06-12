
#include "ConnectionHandler.h"

// other library includes
#include <network/Server.h>
#include <network/Client.h>
#include <utils/time/Time.h>
#include <utils/Logger.h>
#include <utils/TimeHelper.h>

// project file includes
#include "states_application/BroadCastState.h"
#include "states_application/WaitForConnectionsState.h"
#include "NotificationTypes.h"
#include "ResultLogger.h"

namespace core {

Application::~Application() {
  stopServer();
}

void Application::setMachines(const std::vector<MachinePtr> &aMachines) {
  // Set machines
  firstMachinesInLine.clear();
  lastMachineInLine.clear();
  machines = aMachines;
  for (const auto &machine : machines) {
    machine->createInitialBuffers();
  }

  // Links all buffers (for each product type in production line)
  for (const auto &product : productionLine->getProducts()) {
    auto productId = product->getId();
    for (const auto &machine : machines) {
      if (!machine->hasConfiguration(productId)) {
        // Machine doesn't have a configuration for this product.
        continue;
      }
      for (const auto &inputBufferPair : machine->getInputBuffers(productId)) {
        if (auto previousMachineObj = getMachine(inputBufferPair.first)) {
          previousMachineObj->setOutputBuffer(productId, inputBufferPair.second);
        } else {
          // This machine is the first in line because it doesnt have a previous machine
          firstMachinesInLine[productId].emplace_back(machine);
        }
      }
      if (machine->isLastInLine(productId)) {
        // This machine is last in line
        lastMachineInLine[productId] = machine;
      }
    }
  }
  std::stringstream stream;
  for (const auto &machineList : firstMachinesInLine) {
    stream << std::endl << "Machines for product: " << productionLine->getProductById(machineList.first)->getName()
           << std::endl;
    for (const auto &machine : machineList.second) {
      for (const auto &input : machine->getInputBuffers(machineList.first)) {
        input.second->debugPrintBuffersChain(stream);
      }
    }
  }
  stream << std::endl;
  utils::Logger::log(stream.str());
}

MachinePtr Application::getMachine(uint16_t machineId) {
  auto machineItr = std::find_if(machines.begin(), machines.end(),
                                 [machineId](const MachinePtr &machine) { return machine->getId() == machineId; });
  return (machineItr == machines.end()) ? nullptr : *machineItr;
}

const std::vector<MachinePtr> &Application::getMachines() const {
  return machines;
}

void Application::setupNetwork() {
  if (server && server->isRunning()) {
    return;
  }

  communication::ConnectionHandler connectionHandler;
  handleNotificationsFor(connectionHandler);

  serverThread = manager.runServiceThread();
  server = manager.createServer(std::make_shared<communication::ConnectionHandler>(connectionHandler), 50);
  server->start();
}

void Application::handleNotification(const patterns::notifyobserver::NotifyEvent &notification) {
  // TODO: move the case implementation to own method (or not?)

  switch (notification.getEventId()) {
    case NotifyEventIds::eApplicationRegisterMachine: {
//      auto time = notification.getArgumentAsType<uint64_t>(0); // Unused at the moment
      auto id = notification.getArgumentAsType<uint16_t>(1);
      auto connection = notification.getArgumentAsType<network::ConnectionPtr>(2);
      onHandleRegisterNotification(id, connection);
      break;
    }
    case NotifyEventIds::eApplicationMachineDisconnected: {
//      auto time = notification.getArgumentAsType<uint64_t>(0); // Unused at the moment
      auto id = notification.getArgumentAsType<uint16_t>(1);
      onHandleMachineDisconnected(id);
      break;
    }

    case NotifyEventIds::eApplicationOK: {
//      auto time = notification.getArgumentAsType<uint64_t>(0); // Unused at the moment
      auto id = notification.getArgumentAsType<uint16_t>(1);
      auto status = notification.getArgumentAsType<models::Machine::MachineStatus>(2);
      onHandleOKNotification(id, status);
      break;
    }

    case NotifyEventIds::eApplicationNOK: {
//      auto time = notification.getArgumentAsType<uint64_t>(0); // Unused at the moment
      auto id = notification.getArgumentAsType<uint16_t>(1);
      auto errorCode = notification.getArgumentAsType<models::Machine::MachineErrorCode>(2);
      onHandleNOKNotification(id, errorCode);
      break;
    }

    case NotifyEventIds::eApplicationProductAddedToBuffer: {
      auto machineId = notification.getArgumentAsType<uint16_t>(1);
      onHandleProductAddedToBufferNotification(machineId);
      break;
    }

    case NotifyEventIds::eApplicationProductTakenFromBuffer: {
      auto machineId = notification.getArgumentAsType<uint16_t>(1);
      onHandleProductTakenFromBufferNotification(machineId);
      break;
    }

    default: {
      std::cerr << "unhandled notification with id " << notification.getEventId() << std::endl;
      break;
    }
  }
}

void Application::onHandleRegisterNotification(uint16_t id, const network::ConnectionPtr &connection) {

  auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeMachineRegistered);
  event->addArgument(id);
  event->addArgument(connection);
  scheduleEvent(event);
}

void Application::onHandleMachineDisconnected(uint16_t id) {
  auto event = createStateEvent(applicationstates::kEventTypeMachineDisconnected);
  event->addArgument(id);
  scheduleEvent(event);
}

void Application::onHandleOKNotification(uint16_t id, models::Machine::MachineStatus status) {
  auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeMachineStatusUpdate);
  event->setArgument(0, id);
  event->setArgument(1, status);
  scheduleEvent(event);
}

void Application::onHandleNOKNotification(uint16_t id, models::Machine::MachineErrorCode errorCode) {
  switch (errorCode) {
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

void Application::onHandleProductTakenFromBufferNotification(uint16_t machineId) {
  auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeMachineProductTakenFromBuffer);
  event->setArgument(0, machineId);
  scheduleEvent(event);
}

void Application::onHandleProductAddedToBufferNotification(uint16_t machineId) {
  auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeMachineProductAddedToBuffer);
  event->setArgument(0, machineId);
  scheduleEvent(event);
}

void Application::setStartState() {
  auto startState = std::make_shared<applicationstates::WaitForConnectionsState>(*this);
  setCurrentState(startState);
}

bool Application::checkAllMachinesRegistered() {
  for (const auto &machine : machines) {
    if (!machine->isConnected()) {
      return false;
    }
  }
  auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeAllMachinesRegistered);
  scheduleEvent(event);
  return true;
}

void Application::registerMachine(uint16_t machineId, network::ConnectionPtr connection) {
  auto machine = getMachine(machineId);
  if (machine) {
    machine->setConnection(connection);

    checkAllMachinesRegistered();
  }
}

void Application::stopServer() {
  manager.stop();
  if (serverThread && serverThread->joinable()) {
    serverThread->join();
  }
}

void Application::setProductionLine(const models::ProductionLinePtr &productionLine) {
  this->productionLine = productionLine;
  for (const auto &product : productionLine->getProducts()) {
    productPorportions[product->getId()] = product->getProportion();
  }
}

void Application::executeScheduler() {
  shouldChangeProduction();
  for (const auto &machine : machines) {
    machine->doNextAction();
  }
}

void Application::prepareScheduler() {
  auto configId = currentProductId;
  if (configId == 0) {
    // First time, all buffers are empty etc. so no problem changing
    if (productionLine && !productionLine->getProducts().empty()) {
      configId = productionLine->getProducts().front()->getId();
    }
    changeProductionLineProduct(configId);
    createAndScheduleStateEvent(applicationstates::kEventTypeCanSchedule);
  } else if (!shouldChangeProduction()) {
    // Ccontinue producing what we were doing yesterday
    changeProductionLineProduct(currentProductId);
    createAndScheduleStateEvent(applicationstates::kEventTypeCanSchedule);
  }

}

void Application::changeProductionLineProduct(uint16_t productId) {
  for (const auto &machine : machines) {
    machine->prepareReconfigure(productId, currentProductId == 0);
  }
  currentProductId = productId;
  momentStartingCurrentProduct = utils::Time::getInstance().getCurrentTime();
}

bool Application::setMachineStatus(uint16_t machineId, Machine::MachineStatus status) {
  auto machine = getMachine(machineId);
  if (machine) {
    machine->setStatus(status);
    return true;
  }
  return false;
}

bool Application::shouldChangeProduction() {
  static const uint16_t threeHoursInMinutes = 180;
  static uint64_t timeSinceLastChange = utils::Time::getInstance().getCurrentTime();
  // Don't change if not yet 3 hours passed since last change, or if it's < three hours before closing
  if (timeSinceLastChange + (threeHoursInMinutes * 60000) > utils::Time::getInstance().getCurrentTime() ||
      utils::TimeHelper::getInstance().isClosingTime(threeHoursInMinutes)) {
    return false;
  }
  // Get produced proportions
  std::map<uint16_t, uint64_t> producedProportions;
  auto newId = currentProductId;
  for (const auto &productPorportion : productPorportions) {
    auto &productId = productPorportion.first;
    producedProportions[productId] =
        lastMachineInLine[productId]->getAmountProcessed(productId) / productPorportion.second;
  }
  // Check if there is another product which is ~150 products behind
  for (const auto &producedProportion : producedProportions) {
    if (producedProportion.second + 150 < producedProportions[newId]) {
      newId = producedProportion.first;
    }
  }
  if (currentProductId == newId) {
    // No change :)
    return false;
  }
  auto event = createStateEvent(applicationstates::kEventTypeProductionChange);
  event->setArgument(0, newId);
  scheduleEvent(event);
  return true;
}

void Application::takeProductsFromBuffer(uint16_t machineId) {
  auto machine = getMachine(machineId);
  if (machine) {
    machine->takeProductsFromInputBuffers();
  }
}

void Application::addProductsToBuffer(uint16_t machineId) {
  auto machine = getMachine(machineId);
  if (machine) {
    machine->placeProductsInOutputBuffer();
  }
}

void Application::saveMachineStatistics() {
  auto currentTime = utils::Time::getInstance().getCurrentTime();
  if (machineStatistics[currentTime].empty()) {
    for (auto &machine : machines) {
      machineStatistics[currentTime].push_back(machine->getStatistics());
    }
  }
}

void Application::calculateFinalStatistics() {
  if(machineStatistics.empty()){
    return;
  }

  finalStatistics.clear();

  for (auto &machine : machines) {
    std::vector<models::MachineStatisticsPtr> stats;

    for (auto &item : machineStatistics) {
      for (auto &stat : item.second) {
        if (stat->getMachineId() == machine->getId()) {
          stats.push_back(stat);
        }
      }
    }

    if(stats.size() == 0){
      break;
    }

    std::map<uint16_t, uint32_t> totalProduced;
    std::map<uint16_t, uint32_t> totalLost;
    std::map<uint16_t, uint16_t> avgProduced;
    std::map<uint16_t, uint16_t> avgLost;
    uint64_t totalProductionTime = 0;
    uint64_t totalIdleTime = 0;
    uint64_t totalDownTime = 0;
    uint64_t totalConfigureTime = 0;

    for (auto &stat : stats) {
      for (auto &item : stat->getProducedProducts()) {
        totalProduced[item.first] += item.second;
      }
      for (auto &item : stat->getLostProducts()) {
        totalLost[item.first] += item.second;
      }
      totalProductionTime += stat->getProductionTime();
      totalIdleTime += stat->getIdleTime();
      totalDownTime += stat->getDownTime();
      totalConfigureTime += stat->getConfigureTime();
    }

    auto nStats = stats.size();

    for (auto &item : totalProduced) {
      avgProduced[item.first] = static_cast<uint16_t >(item.second / nStats);
    }

    for (auto &item : totalLost) {
      avgLost[item.first] = static_cast<uint16_t>(item.second / nStats);
    }

    finalStatistics.emplace_back(
        machine->getId(),
        machine->getName(),
        avgProduced,
        avgLost,
        static_cast<uint32_t>(totalDownTime / nStats),
        static_cast<uint32_t>(totalProductionTime / nStats),
        static_cast<uint32_t>(totalIdleTime / nStats),
        static_cast<uint32_t>(totalConfigureTime / nStats),
        totalProduced,
        totalLost,
        machine->getTimesBroken(),
        machine->calculateMTBF()
    );
  }
}

void Application::logFinalStatistics() {
  calculateFinalStatistics();
  ResultLogger::getInstance().logStatistics(machineStatistics, finalStatistics);
}

void Application::prepareForShutdown() {
  for (const auto &machine : machines) {
    machine->youreDoneForToday();
  }
}

void Application::workDayOver() {
  // Woohoo!
}

void Application::checkTimeToStartAgain() {

}

bool Application::checkAllMachinesIdle(bool completelyIdle) {
  for (const auto &machine : machines) {
    if (!machine->isIdle(completelyIdle)) {
      return false;
    }
  }
  createAndScheduleStateEvent(applicationstates::kEventTypeAllMachinesIdle);
  return true;
}

bool Application::checkAllMachinesDisconnected() {
  for (const auto &machine : machines) {
    if (machine->isConnected()) {
      return false;
    }
  }
  createAndScheduleStateEvent(applicationstates::kEventTypeAllMachinesDisconnected);
  return true;
}

}
