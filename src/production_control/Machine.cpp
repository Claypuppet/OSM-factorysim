
#include <iostream>
#include <memory>
#include <utils/Logger.h>
#include <utils/time/Time.h>
#include <models/Configuration.h>
#include "Machine.h"
#include "InfiniteBuffer.h"
#include "ResultLogger.h"

namespace core {

Machine::Machine(const models::Machine &aMachine)
    : models::Machine(aMachine),
      status(kMachineStatusDisconnected),
      awaitingResponse(false),
      connection(),
      productInProcess(),
      prepareConfigureId(0),
      currentConfigId(0),
      nextAction(kNextActionTypeProcessProduct),
      lastStatusChange(0),
      producedProducts(),
      lostProducts(),
      timeSpendInState(),
      timesBroken(0),
      inputBuffers(),
      outputBuffers() {
}

void Machine::setConnection(const network::ConnectionPtr &aConnection) {
  connection = aConnection;
  if (connection && connection->isConnected()) {
    lastStatusChange = utils::Time::getInstance().getCurrentTime();
    setStatus(kMachineStatusInitializing);
  }
}

bool Machine::isConnected() const {
  return !!connection;
}

void Machine::sendMessage(network::Message &message) {
  message.setTime(utils::Time::getInstance().getCurrentTime());
  if (isConnected()) {
    awaitingResponse = true;
    connection->writeMessage(message);
  }
}
void Machine::sendStartProcessMessage() {
  network::Message message(network::Protocol::kAppMessageTypeStartProcess);
  sendMessage(message);
}

void Machine::sendConfigureMessage(uint16_t configureId) {
  network::Message message(network::Protocol::kAppMessageTypeReconfigure);
  message.setBodyObject(configureId);
  sendMessage(message);
}

void Machine::prepareReconfigure(uint16_t configureId, bool firstTime /* = false */) {
  if (const auto &configuration = getConfigurationById(configureId)) {
    // Configuration exists
    prepareConfigureId = configureId;
    nextAction = kNextActionTypeReconfigure;
  }
  else if (firstTime) {
    // First config, but requested config doest not exist, machine will initialize in first known config
    if (!configurations.empty()) {
      // Configuration exists
      prepareConfigureId = configurations.front()->getProductId();
      nextAction = kNextActionTypeReconfigure;
    }
  }
}

const InputBuffersPerMachineMap &Machine::getCurrentInputBuffers() const {
  return inputBuffers.at(currentConfigId);
}

const InputBuffersPerMachineMap &Machine::getInputBuffers(uint16_t productId) const {
  return inputBuffers.at(productId);
}

const BufferPtr &Machine::getCurrentOutputBuffer() const {
  return outputBuffers.at(currentConfigId);
}

const BufferPtr &Machine::getOutputBuffer(uint16_t productId) const {
  return outputBuffers.at(productId);
}

const InputBuffersPerConfigMap &Machine::getInputBuffers() const {
  return inputBuffers;
}

const OutputBuffersPerConfigMap &Machine::getOutputBuffers() const {
  return outputBuffers;
}

void Machine::setOutputBuffer(uint16_t productId, BufferPtr outputBuffer) {
  auto self = shared_from_this();
  outputBuffers[productId] = outputBuffer;
  outputBuffer->setPutterMachine(self);
}

void Machine::createInitialBuffers() {
  auto self = shared_from_this();

  for (const auto &machineConfiguration : configurations) {
    auto productId = machineConfiguration->getProductId();

    // set outputbuffer based on config
    auto outputBuffer = std::make_shared<InfiniteBuffer>(productId);
    outputBuffer->setPutterMachine(self);
    outputBuffers[productId] = outputBuffer;

    // Set input buffer as infinite buffer for each previous buffer without machine
    for (const auto &previousMachine : machineConfiguration->getPreviousMachines()) {
      BufferPtr buffer;

      auto bufferSize = previousMachine->getInputBufferSize();
      if (bufferSize > 0 && previousMachine->getMachineId() > 0) {
        // Buffer with size
        buffer = std::make_shared<Buffer>(self, productId, bufferSize);
      }
      else {
        // Infinite buffer
        buffer = std::make_shared<InfiniteBuffer>(self, productId);
      }
      inputBuffers[machineConfiguration->getProductId()][previousMachine->getMachineId()] = buffer;
    }
  }
}

void Machine::setStatus(Machine::MachineStatus newStatus) {
  // Do specific action based on new status
  switch (newStatus) {
    case kMachineStatusIdle: {
      if (status == kMachineStatusConfiguring) {
        // Don (re)configuring
        currentConfigId = prepareConfigureId;
        nextAction = kNextActionTypeProcessProduct;
        ResultLogger::getInstance().machineConfigChanged(id, currentConfigId);
      }
      awaitingResponse = false;
      break;
    }
    case kMachineStatusProcessingProduct: {
      // Started processing product (product taken from buffer)
      break;
    }
    case kMachineStatusConfiguring: {
      if (status == kMachineStatusBroken) {
        // Went from broken to configuring
        std::stringstream stream;
        stream << "machine \"" << name << "\" repaired @ " << utils::Time::getInstance().getCurrentTime();
        utils::Logger::log(stream.str());
      }
      break;
    }
    case kMachineStatusBroken: {
      // Broke while processing product , product lost
      ++timesBroken;
      lostProducts[currentConfigId] += productInProcess.size();
      std::queue<ProductPtr> empty;
      std::swap(productInProcess, empty);
      std::stringstream stream;
      stream << "machine \"" << name << "\" broke @ " << utils::Time::getInstance().getCurrentTime();
      utils::Logger::log(stream.str());
      break;
    }
    default:
      // Nothing interesting happening
      break;
  }
  // Keep track of statistics
  auto now = utils::Time::getInstance().getCurrentTime();
  timeSpendInState[status] += (now - lastStatusChange);
  lastStatusChange = now;

  // Change status
  status = newStatus;
  ResultLogger::getInstance().machineStatusUpdate(id, status);
}

Machine::MachineStatus Machine::getStatus() {
  return status;
}

bool Machine::canDoAction() {
  // can't do action if not connected or waiting for response
  if (!isConnected() || awaitingResponse) {
    return false;
  }
  switch (nextAction) {
    case kNextActionTypeProcessProduct:{
      // If machine is not in idle state, it can't do much...
      if (status != kMachineStatusIdle) {
        return false;
      }
      // Check if needed products in input buffers
      for (const auto &inputBuffer : getCurrentInputBuffers()) {
        auto previous = getConfigurationById(currentConfigId)->getPreviousMachineById(inputBuffer.first);
        if (!inputBuffer.second->checkAmountInBuffer(previous->getNeededProducts())) {
          return false;
        }
      }
      // Check if there is room in the output buffer
      // NOTE: currently we only support machines that produce 1 product per process (plus current products in process)
      return getCurrentOutputBuffer()->checkFreeSpaceInBuffer(static_cast<uint32_t>(productInProcess.size() + 1));
    }
    case kNextActionTypeReconfigure:{
      // If machine is wants to reconfigure, we can do that in the init state or idle state
      return status == kMachineStatusIdle || status == kMachineStatusInitializing;
    }
    default:{
      return false;
    }
  }
}

void Machine::doNextAction() {
  if (canDoAction()) {
    switch (nextAction) {
      case kNextActionTypeProcessProduct:
        sendStartProcessMessage();
        break;
      case kNextActionTypeReconfigure:
        sendConfigureMessage(prepareConfigureId);
        break;
    }
  }
}

void Machine::takeProductsFromInputBuffers() {
  if (!currentConfigId) {
    return;
  }
  for (const auto &inputBuffer : getCurrentInputBuffers()) {
	auto previous = getConfigurationById(currentConfigId)->getPreviousMachineById(inputBuffer.first);
	auto itemsTaken = inputBuffer.second->takeFromBuffer(previous->getNeededProducts());
	// NOTE: We will only track one (first) product
    productInProcess.emplace(itemsTaken.front());
  }
}

void Machine::placeProductsInOutputBuffer() {
  if (!currentConfigId) {
    return;
  }
  if (productInProcess.empty()) {
    throw std::runtime_error("Trying to put a rotten potato in output buffer! Send help!");
  }
  const auto outputBuffer = getCurrentOutputBuffer();
  outputBuffer->putInBuffer(productInProcess.front());
  ++producedProducts[currentConfigId];
  productInProcess.pop();
  ResultLogger::getInstance().bufferContentsChanged(id, currentConfigId, outputBuffer->getAmountInBuffer());
}

const std::vector<models::PreviousMachinePtr> &Machine::getPreviousMachines(uint16_t configureId) {
  return getConfigurationById(configureId)->getPreviousMachines();
}

const std::vector<std::shared_ptr<models::PreviousMachine>> &Machine::getPreviousMachines() {
  return getPreviousMachines(currentConfigId);
}

bool Machine::isWaitingForResponse() {
  return awaitingResponse;
}

uint64_t Machine::getAmountProcessed(uint16_t productId) {
  return getOutputBuffer(productId)->getTotalProcessed();
}

bool Machine::isLastInLine(uint16_t productId) {
  return getOutputBuffer(productId)->isLastInLine();
}

const std::map<Machine::MachineStatus, uint32_t> &Machine::getTimeSpendInState() const {
  return timeSpendInState;
}

uint16_t Machine::getTimesBroken() const {
  return timesBroken;
}

models::MachineStatisticsPtr Machine::getStatistics() {
  uint32_t productionTime = timeSpendInState[models::Machine::kMachineStatusProcessingProduct];
  uint32_t idleTime = timeSpendInState[models::Machine::kMachineStatusIdle];
  uint32_t configureTime = timeSpendInState[models::Machine::kMachineStatusConfiguring]
      + timeSpendInState[models::Machine::kMachineStatusInitializing];
  uint32_t downTime = timeSpendInState[models::Machine::kMachineStatusBroken];
  auto stats = std::make_shared<models::MachineStatistics>(id,
                                                              producedProducts,
                                                              lostProducts,
                                                              downTime,
                                                              productionTime,
                                                              idleTime,
                                                              configureTime);
  timeSpendInState.clear();
  producedProducts.clear();
  lostProducts.clear();
  return stats;
}

}