
#include <iostream>

#include "Machine.h"

namespace core {

Machine::Machine(const models::Machine &aMachine) :
    models::Machine(aMachine) {
}

Machine::Machine(const Machine &aMachine) :
    models::Machine(aMachine) {
}

Machine &Machine::operator=(const Machine &rhs) {
  if (this != &rhs) {
    models::Machine::operator=(rhs);
    connection = rhs.connection;
  }
  return *this;
}

void Machine::setConnection(Network::ConnectionPtr aConnection) {
  connection = aConnection;
}

bool Machine::isConnected() const {
  return !!connection;
}

void Machine::sendMessage(const Network::Message &msg) {
  if (isConnected()) {
    connection->writeMessage(msg);
  }
}
void Machine::sendStartProcessMessage() {
  Network::Message message(Network::Protocol::kAppMessageTypeStartProcess);
  sendMessage(message);
}

    void Machine::sendConfigureMessage(uint32_t configureId) {
        Network::Message message(Network::Protocol::kAppMessageTypeReconfigure, std::to_string(configureId));
    }

}