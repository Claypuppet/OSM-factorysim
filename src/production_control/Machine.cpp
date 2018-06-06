
#include <iostream>
#include <memory>
#include <utils/Logger.h>
#include <utils/time/Time.h>
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
      timeSpendInState(),
      timesBroken(0),
      inputBuffers(),
      outputBuffers() {
}

Machine::Machine(const Machine &aMachine)
    : models::Machine(aMachine),
      status(kMachineStatusDisconnected),
      awaitingResponse(false),
      connection(),
      productInProcess(),
      prepareConfigureId(0),
      currentConfigId(0),
      nextAction(kNextActionTypeProcessProduct),
      lastStatusChange(0),
      timeSpendInState(),
      timesBroken(0),
      inputBuffers(),
      outputBuffers() {
}

void Machine::setConnection(const network::ConnectionPtr &aConnection) {
  connection = aConnection;
  if(connection && connection->isConnected()){
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

void Machine::prepareReconfigure(uint16_t configureId, bool firstTime /* = false */) {
  if(const auto &configuration = getConfigurationById(configureId)){
    // Configuration exists
    prepareConfigureId = configureId;
    nextAction = kNextActionTypeReconfigure;
  }
  else if(firstTime){
    // First config, but requested config doest not exist, machine will initialize in first known config
    if(!configurations.empty()){
      // Configuration exists
      prepareConfigureId = configurations.front()->getProductId();
      nextAction = kNextActionTypeReconfigure;
    }
  }
}

void Machine::sendConfigureMessage(uint16_t configureId) {
  currentConfigId = static_cast<uint16_t>(configureId);
  network::Message message(network::Protocol::kAppMessageTypeReconfigure);
  message.setBodyObject(configureId);
  sendMessage(message);
//  std::stringstream ss;
//  ss << "--sending configure message to machine " << id;
//  utils::Logger::log(ss.str());
}

const BufferList &Machine::getCurrentInputBuffers() const {
  return inputBuffers.at(currentConfigId);
}

const BufferPtr &Machine::getCurrentOutputBuffer() const {
  return outputBuffers.at(currentConfigId);
}

const BufferList &Machine::getInputBuffers(uint16_t productId) const {
  return inputBuffers.at(productId);
}

const BufferPtr &Machine::getOutputBuffer(uint16_t productId) const {
  return outputBuffers.at(productId);
}

const InputBuffersMap &Machine::getInputBuffers() const {
  return inputBuffers;
}

const OutputBuffersMap &Machine::getOutputBuffers() const {
  return outputBuffers;
}

void Machine::addInputBuffer(uint16_t productId, BufferPtr inputbuffer) {
  auto self = shared_from_this();
  inputBuffers[productId].emplace_back(inputbuffer);
  inputbuffer->addToMachine(self);
}

void Machine::createInitialBuffers() {
  auto self = shared_from_this();
  for (const std::shared_ptr<models::MachineConfiguration> &machineConfiguration : configurations) {
    auto productId = machineConfiguration->getProductId();
    BufferPtr buffer;

    auto bufferSize = machineConfiguration->getgetOutputBufferSize();
    if (bufferSize > 0) {
      // Buffer with size
      buffer = std::make_shared<Buffer>(self, productId, machineConfiguration->getOutputBufferSize());
    } else {
      // Infinite buffer
      buffer = std::make_shared<InfiniteBuffer>(self, productId);
    }

    // set outputbuffer based on config
    outputBuffers[productId] = buffer;

    // Set input buffer as infinite buffer for each previous buffer without machine
    for (const auto &previousMachine : machineConfiguration->getPreviousMachines()) {
      if (previousMachine->getMachineId() == 0) {
        auto inputBuffer = std::make_shared<InfiniteBuffer>(productId);
        inputBuffers[machineConfiguration->getProductId()].emplace_back(inputBuffer);
        inputBuffer->addToMachine(self);
      }
    }
  }
}

void Machine::setStatus(Machine::MachineStatus newStatus) {
  // Do specific action based on new status
  switch (newStatus) {
    case kMachineStatusIdle: {
      awaitingResponse = false;
      if (status == kMachineStatusProcessingProduct) {
        // Don processing product
        placeProductsInOutputBuffer();
      }
      else if (status == kMachineStatusConfiguring) {
        // Don (re)configuring
        currentConfigId = prepareConfigureId;
        nextAction = kNextActionTypeProcessProduct;
        ResultLogger::getInstance().machineConfigChanged(id, currentConfigId);
      }
      break;
    }
    case kMachineStatusProcessingProduct: {
      // Started processing product (product taken from buffer)
      takeProductsFromInputBuffers();
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
      productInProcess = nullptr;
      ++timesBroken;
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
  timeSpendInState[status] += (now -lastStatusChange);
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
  // If machine is wants to reconfigure, we can do that in the init state or idle state
  if(nextAction == kNextActionTypeReconfigure){
    return status == kMachineStatusInitializing || status == kMachineStatusIdle;
  }
  // If machine is not in idle state, it can't do much...
  if(status != kMachineStatusIdle){
    return false;
  }
  // Check if needed products in input buffers (previous machines)
  for (const auto &inputBuffer : getCurrentInputBuffers()) {
    auto previous = getConfigurationById(currentConfigId)->getPreviousMachineById(inputBuffer->getFromMachineId());
    if (!inputBuffer->checkAmountInBuffer(previous->getNeededProducts())) {
      return false;
    }
  }
  // Final check: check if enough space in output buffer
  // NOTE: currently we only support machines that produce 1 product per process
  return getCurrentOutputBuffer()->checkFreeSpaceInBuffer(1);
}

void Machine::doNextAction() {
  if(canDoAction()){
    switch (nextAction){
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
	auto previous = getConfigurationById(currentConfigId)->getPreviousMachineById(inputBuffer->getFromMachineId());
	auto itemsTaken = inputBuffer->takeFromBuffer(previous->getNeededProducts());
	// NOTE: We will only track one (first) product
	productInProcess = itemsTaken.front();
  }
}

void Machine::placeProductsInOutputBuffer() {
  if (!currentConfigId) {
    return;
  }
  if (!productInProcess){
    throw std::runtime_error("Trying to put a rotten potato in output buffer! Send help!");
  }
  const auto outputBuffer = getCurrentOutputBuffer();
  outputBuffer->putInBuffer(productInProcess);
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

const std::map<Machine::MachineStatus, uint64_t> &Machine::getTimeSpendInState() const {
  return timeSpendInState;
}

uint16_t Machine::getTimesBroken() const {
  return timesBroken;
}

}