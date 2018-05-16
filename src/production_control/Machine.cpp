
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
  Network::Message message(Network::Protocol::kAppMessageTypeReconfigure, std::to_string(configureId));
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

void Machine::setInputBuffers(const std::map<uint16_t, BufferPtr> &aInputBuffers) {
  inputBuffers = aInputBuffers;
}

void Machine::createBuffers() {
  for (const auto &config : configurations){
    auto bufferSize = config.getInputBufferSize();
    BufferPtr buffer;
    if(bufferSize) {
      buffer = std::make_shared<Buffer>(config.getInputBufferSize());
    }
    else {
      buffer = std::make_shared<Buffer>();
    }
    inputBuffers[config.getProductId()] =  buffer;
  }
}

}