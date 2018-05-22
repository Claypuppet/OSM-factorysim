
#include <iostream>
#include <memory>
#include <utils/Logger.h>
#include "Machine.h"

namespace core {

Machine::Machine(const models::Machine &aMachine)
	: models::Machine(aMachine), status(kMachineStatusWaitingForConfig), awaitingResponse(false) {
}

Machine::Machine(const Machine &aMachine)
	: models::Machine(aMachine), status(kMachineStatusWaitingForConfig), awaitingResponse(false) {
}

Machine &Machine::operator=(const Machine &rhs) {
  if (this != &rhs) {
	models::Machine::operator=(rhs);
	connection = rhs.connection;
  }
  return *this;
}

void Machine::setConnection(const network::ConnectionPtr &aConnection) {
  connection = aConnection;
}

bool Machine::isConnected() const {
  return !!connection;
}

void Machine::sendMessage(const network::Message &message) {
  if (isConnected()) {
	connection->writeMessage(message);
  }
  awaitingResponse = true;
}
void Machine::sendStartProcessMessage() {
  network::Message message(network::Protocol::kAppMessageTypeStartProcess);
  sendMessage(message);
  std::stringstream ss;
  ss << "--sending process message to machine " << id;
  utils::Logger::log(ss.str());
}

void Machine::sendConfigureMessage(uint32_t configureId) {
  network::Message message(network::Protocol::kAppMessageTypeReconfigure);
  message.setBodyObject(configureId);
  sendMessage(message);
  std::stringstream ss;
  ss << "--sending configure message to machine " << id;
  utils::Logger::log(ss.str());
}

const BufferList &Machine::getCurrentInputBuffers() const {
  return currentInputBuffers;
}

const BufferPtr &Machine::getCurrentOutputBuffer() const {
  return currentOutputBuffer;
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

void Machine::setInputBuffers(uint16_t productId, BufferPtr inputbuffer) {
  inputBuffers[productId].emplace_back(inputbuffer);
}

void Machine::createInitialBuffers() {
  auto self = shared_from_this();
  for (const auto &config : configurations) {
	BufferPtr buffer;
	auto bufferSize = config.getOutputBufferSize();
	if (bufferSize) {
	  // Buffer with size
	  buffer = std::make_shared<Buffer>(self, config.getOutputBufferSize());
	} else {
	  // Infinite buffer
	  buffer = std::make_shared<Buffer>(self);
	}
	// set outputbuffer based on config
	outputBuffers[config.getProductId()] = buffer;
	// Set input buffer as infinite buffer, this will be set by the application later if needed.
	for (const auto &previousMachine : config.getPreviousMachines()) {
	  inputBuffers[config.getProductId()].emplace_back(std::make_shared<Buffer>(self));
	}
  }
}

void Machine::useBuffersForConfig(uint16_t configureId) {
  currentInputBuffers = inputBuffers[configureId];
  currentOutputBuffer = outputBuffers[configureId];
}

std::vector<models::PreviousMachine> Machine::getPreviousMachines(uint16_t configureId) {
  std::vector<models::PreviousMachine> previousMachines;
  return previousMachines;
}
void Machine::setStatus(Machine::MachineStatus newStatus) {
  status = newStatus;
  if (status == kMachineStatusIdle) {
	awaitingResponse = false;
  }
}
Machine::MachineStatus Machine::getStatus() {
  return status;
}

bool Machine::canDoAction(uint16_t configureId) {
  for (const auto &inputBuffer : currentInputBuffers) {
	auto previous = getConfigurationById(configureId).getPreviousMachineById(inputBuffer->getFromMachineId());
	if (!inputBuffer->checkAmountInBuffer(previous.getNeededProducts())) {
	  return false;
	}
  }
  return !awaitingResponse && status == kMachineStatusIdle;
}
}