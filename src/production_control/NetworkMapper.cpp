//
// Created by klei on 5/10/18.
//

#include "NetworkMapper.h"

namespace core {

void NetworkMapper::registerMachineConnection(const Network::ConnectionPtr &connection, uint16_t machineId) {
  auto sessionId = static_cast<uint32_t>(connection->getSessionId());
  machineConnectionMap[sessionId] = machineId;
}

void NetworkMapper::disconnectMachineConnection(const Network::ConnectionPtr &connection) {
  auto sessionId = static_cast<uint32_t>(connection->getSessionId());
  machineConnectionMap.erase(sessionId);
}

uint16_t NetworkMapper::getMachineIdForConnection(const Network::ConnectionPtr &connection) const {
  auto sessionId = static_cast<uint32_t>(connection->getSessionId());
  return machineConnectionMap.at(sessionId);
}

}