//
// Created by klei on 5/10/18.
//

#include "NetworkMapper.h"

namespace communication {

void NetworkMapper::registerMachineConnection(const network::ConnectionPtr &connection, uint16_t machineId) {
  auto sessionId = static_cast<uint32_t>(connection->getSessionId());
  machineConnectionMap[sessionId] = machineId;
}

void NetworkMapper::disconnectMachineConnection(const network::ConnectionPtr &connection) {
  auto sessionId = static_cast<uint32_t>(connection->getSessionId());
  machineConnectionMap.erase(sessionId);
}

uint16_t NetworkMapper::getMachineIdForConnection(const network::ConnectionPtr &connection) const {
  auto sessionId = static_cast<uint32_t>(connection->getSessionId());
  try{
    return machineConnectionMap.at(sessionId);
  }
  catch (const std::exception &e) {
    throw std::range_error("Received a message from machine before the machine registered!");
  }
}

}