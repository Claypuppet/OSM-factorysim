
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
        }
        else {
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
  for (const auto &machine : machines) {
    machine->doNextAction();
  }
  shouldChangeProduction();
}

void Application::prepareScheduler() {
  auto configId = currentProductId;
  if (configId != 0 && shouldChangeProduction()) {
    // Should change product,
    return;
  }
  else if (configId == 0) {
    // First time, all buffers are empty etc. so no problem changing
    if (productionLine && !productionLine->getProducts().empty()) {
      configId = productionLine->getProducts().front()->getId();
    }
  }
  // Else continue producing what we were doing yesterday
  changeProductionLineProduct(configId);
  createAndScheduleStateEvent(applicationstates::kEventTypeCanSchedule);

}

void Application::changeProductionLineProduct(uint16_t productId) {
  for (const auto &machine : machines) {
    machine->prepareReconfigure(productId, currentProductId == 0);
  }
  currentProductId = productId;
  momentStartingCurrentProduct = utils::Time::getInstance().getCurrentTime();
  ++timesReconfigured;
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

void Application::calculateMachineFinalStatistics() {
  if (machineStatistics.empty()) {
    return;
  }

  machineFinalStatistics.clear();

  for (auto &machine : machines) {
    std::vector<models::MachineStatisticsPtr> stats;

    for (auto &item : machineStatistics) {
      for (auto &stat : item.second) {
        if (stat->getMachineId() == machine->getId()) {
          stats.push_back(stat);
        }
      }
    }

    if (stats.empty()) {
      break;
    }

    std::map<uint16_t, uint32_t> totalProduced;
    std::map<uint16_t, uint16_t> totalLost;

    std::map<uint16_t, uint64_t> totalIdleTime;
    std::map<uint16_t, uint64_t> totalProductionTime;
    std::map<uint16_t, uint64_t> totalDownTime;
    std::map<uint16_t, uint64_t> totalConfigureTime;

    for (auto &stat : stats) {
      auto productStats = stat->getProductStatistics();
      for (auto &product : productStats) {
        auto productId = product.getProductId();
        totalProduced[productId] += product.getProduced();
        totalLost[productId] += product.getLost();
        totalIdleTime[productId] += product.getIdleTime();
        totalProductionTime[productId] += product.getProductionTime();
        totalDownTime[productId] += product.getDownTime();
        totalConfigureTime[productId] += product.getConfigureTime();
      }
    }

    std::vector<models::MachineProductFinalStatistics> productFinalStats;

    auto nStats = static_cast<uint16_t>(stats.size());

    for (auto &item : totalProduced) {
      auto productId = item.first;
      productFinalStats.emplace_back(models::MachineProductFinalStatistics(
          productId,
          totalProduced[productId],
          static_cast<uint16_t>(totalProduced[productId] / nStats),
          totalLost[productId],
          totalLost[productId] / nStats,
          static_cast<uint32_t>(totalProductionTime[productId] / nStats),
          static_cast<uint32_t>(totalIdleTime[productId] / nStats),
          static_cast<uint32_t>(totalDownTime[productId] / nStats),
          static_cast<uint32_t>(totalConfigureTime[productId] / nStats)));
    }

    uint64_t downTime = 0;

    for (auto &item : totalDownTime) {
      downTime += item.second;
    }

    machineFinalStatistics.emplace_back(
        models::MachineFinalStatistics(
            machine->getName(),
            machine->getId(),
            machine->calculateMTBF(),
            machine->getTimesBroken(),
            downTime,
            productFinalStats
        )
    );
  }
}

void Application::logFinalStatistics() {
  calculateMachineFinalStatistics();
  ResultLogger::getInstance().logStatistics(machineStatistics, machineFinalStatistics, calculateFinalStatistics());
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
models::FinalStatisticsPtr Application::calculateFinalStatistics() {
  std::map<uint16_t, uint32_t> endProducts;

  for (const auto &item : lastMachineInLine) {
    endProducts[item.first] = static_cast<uint32_t>(item.second->getOutputBuffer(item.first)->getTotalProcessed());
  }

  return std::make_shared<models::FinalStatistics>(endProducts,
                                                   timesReconfigured,
                                                   utils::TimeHelper::i().getTotalHoursWorked());
}

uint16_t Application::getTimesReconfigured() const {
  return timesReconfigured;
}

}
