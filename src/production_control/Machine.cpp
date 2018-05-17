
#include <iostream>
#include <memory>
#include "Machine.h"

namespace core {

Machine::Machine(const models::Machine &aMachine) : models::Machine(aMachine) {
  createBuffers();
}

Machine::Machine(const Machine &aMachine) : models::Machine(aMachine) {
  createBuffers();
}

Machine &Machine::operator=(const Machine &rhs) {
  if (this != &rhs) {
    models::Machine::operator=(rhs);
    connection = rhs.connection;
  }
  return *this;
}

void Machine::setConnection(const Network::ConnectionPtr& aConnection) {
  connection = aConnection;
}

bool Machine::isConnected() const {
  return !!connection;
}

void Machine::sendMessage(const Network::Message &message) {
  if (isConnected()) {
    connection->writeMessage(message);
  }
}
void Machine::sendStartProcessMessage() {
  Network::Message message(Network::Protocol::kAppMessageTypeStartProcess);
  sendMessage(message);
}

void Machine::sendConfigureMessage(uint32_t configureId) {
  Network::Message message(Network::Protocol::kAppMessageTypeReconfigure);
  message.setBodyObject(configureId);
  sendMessage(message);
}

const BufferPtr &Machine::getCurrentInputBuffer() const {
  return currentInputBuffer;
}

const BufferPtr &Machine::getCurrentOutputBuffer() const {
  return currentOutputBuffer;
}

const std::map<uint16_t, BufferPtr> &Machine::getInputBuffers() const {
  return inputBuffers;
}

const std::map<uint16_t, BufferPtr> &Machine::getOutputBuffers() const {
  return outputBuffers;
}

const BufferPtr &Machine::getInputBuffer(uint16_t productId) const {
  return inputBuffers.at(productId);
}

const BufferPtr &Machine::getOutputBuffer(uint16_t productId) const {
  return outputBuffers.at(productId);
}

void Machine::setInputBuffer(uint16_t productId, const BufferPtr &inputBuffer) {
  inputBuffers[productId] = inputBuffer;
}

void Machine::createBuffers() {
  for (const auto &config : configurations){
    BufferPtr buffer;
    auto bufferSize = config.getInputBufferSize();
    if(bufferSize) {
      // Buffer with size
      buffer = std::make_shared<Buffer>(config.getInputBufferSize());
    }
    else {
      // Infinite buffer
      buffer = std::make_shared<Buffer>();
    }
    // set outputbuffer based on config
    outputBuffers[config.getProductId()] = buffer;
    // Set input buffer as infinite buffer, this will be handled by
    inputBuffers[config.getProductId()] = std::make_shared<Buffer>();
  }
}

void Machine::useBuffersForConfig(uint16_t configureId) {
  currentInputBuffer = inputBuffers[configureId];
  currentOutputBuffer = outputBuffers[configureId];
}

uint32_t Machine::getNextMachineId(uint16_t configureId) {
  for (const auto &config : configurations) {
    if (config.getProductId() == configureId){
      return config.getNextMachineId();
    }
  }
}

}