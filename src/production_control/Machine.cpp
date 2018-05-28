
#include <iostream>
#include <memory>
#include <utils/Logger.h>
#include <utils/time/Time.h>
#include "Machine.h"
#include "InfiniteBuffer.h"

namespace core {

Machine::Machine(const models::Machine &aMachine)
	: models::Machine(aMachine), status(kMachineStatusInitializing), awaitingResponse(false) {
}

Machine::Machine(const Machine &aMachine)
	: models::Machine(aMachine), status(kMachineStatusInitializing), awaitingResponse(false) {
}

void Machine::setConnection(const network::ConnectionPtr &aConnection) {
  connection = aConnection;
}

bool Machine::isConnected() const {
  return !!connection;
}

void Machine::sendMessage(network::Message &message) {
  message.setTime(utils::Time::getInstance().getCurrentTime());
  if (isConnected()) {
	connection->writeMessage(message);
    awaitingResponse = true;
  }
}
void Machine::sendStartProcessMessage() {
  network::Message message(network::Protocol::kAppMessageTypeStartProcess);
  sendMessage(message);
  std::stringstream ss;
  ss << "--sending process message to machine " << id;
  utils::Logger::log(ss.str());
}

void Machine::sendConfigureMessage(uint32_t configureId) {
  currentConfigId = static_cast<uint16_t>(configureId);
  network::Message message(network::Protocol::kAppMessageTypeReconfigure);
  message.setBodyObject(configureId);
  sendMessage(message);
  std::stringstream ss;
  ss << "--sending configure message to machine " << id;
  utils::Logger::log(ss.str());
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
  inputBuffers[productId].emplace_back(inputbuffer);
}

void Machine::createInitialBuffers() {
  auto self = shared_from_this();
  for (const auto &config : configurations) {
	BufferPtr buffer;
	auto bufferSize = config.getOutputBufferSize();
	if (bufferSize > 0) {
	  // Buffer with size
	  buffer = std::make_shared<Buffer>(self, config.getOutputBufferSize());
	} else {
	  // Infinite buffer
	  buffer = std::make_shared<InfiniteBuffer>(config.getProductId());
	}
	// set outputbuffer based on config
	outputBuffers[config.getProductId()] = buffer;
	// Set input buffer as infinite buffer for each previous buffer without machine
	for (const auto &previousMachine : config.getPreviousMachines()) {
	  if (previousMachine.getMachineId() == 0){
        inputBuffers[config.getProductId()].emplace_back(std::make_shared<InfiniteBuffer>(config.getProductId()));
	  }
	}
  }
}

void Machine::setCurrentConfig(uint16_t configureId) {
  currentConfigId = configureId;
}

void Machine::setStatus(Machine::MachineStatus newStatus) {
  // Do specific action based on status
  switch (newStatus) {
    case kMachineStatusIdle:{
      awaitingResponse = false;
      if (status == kMachineStatusProcessingProduct){
        // Don processing product
        placeProductsInOutputBuffer();
      }
      break;
    }
    case kMachineStatusProcessingProduct:{
      takeProductsFromInputBuffers();
      break;
    }
    case kMachineStatusBroken:{
      if(status == kMachineStatusProcessingProduct){
        // Broke while processing product, product lost
        processedProduct = nullptr;
      }
      break;
    }
    default:
      // Nothing interesting happening
      break;
  }
  status = newStatus;
}

Machine::MachineStatus Machine::getStatus() {
  return status;
}

bool Machine::canDoAction() {
  // can't do action if not connected, waiting for response or not in idle state
  if (!isConnected() || awaitingResponse || status != kMachineStatusIdle){
    return false;
  }
  // Check if needed products in input buffers (previous machines)
  for (const auto &inputBuffer : getCurrentInputBuffers()) {
	auto previous = getConfigurationById(currentConfigId).getPreviousMachineById(inputBuffer->getFromMachineId());
	if (!inputBuffer->checkAmountInBuffer(previous.getNeededProducts())) {
	  return false;
	}
  }
  // Final check: check if enough space in output buffer
  // NOTE: currently we only support machines that produce 1 product per process
  return getCurrentOutputBuffer()->checkFreeSpaceInBuffer(1);
}

void Machine::takeProductsFromInputBuffers() {
  if(!currentConfigId){
    return;
  }
  for (const auto &inputBuffer : getCurrentInputBuffers()) {
	auto previous = getConfigurationById(currentConfigId).getPreviousMachineById(inputBuffer->getFromMachineId());
	auto itemsTaken = inputBuffer->takeFromBuffer(previous.getNeededProducts());
	// NOTE: We will only track one (first) product
	processedProduct = itemsTaken.front();
  }
}

void Machine::placeProductsInOutputBuffer() {
  if(!currentConfigId){
    return;
  }
  if (!processedProduct){
    throw std::runtime_error("Trying to put a rotten potato in output buffer! Send help!");
  }
  const auto outputBuffer = getCurrentOutputBuffer();
  outputBuffer->putInBuffer(processedProduct);
}

const std::vector<models::PreviousMachine> &Machine::getPreviousMachines(uint16_t configureId) {
  return getConfigurationById(configureId).getPreviousMachines();
}

const std::vector<models::PreviousMachine> &Machine::getPreviousMachines() {
  return getPreviousMachines(currentConfigId);
}
bool Machine::isWaitingForResponse() const {
  return awaitingResponse;
}

}