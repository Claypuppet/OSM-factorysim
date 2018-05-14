//
// Created by klei on 5/10/18.
//

#ifndef PRODUCTION_LINE_CONTROL_NETWORKMAPPER_H
#define PRODUCTION_LINE_CONTROL_NETWORKMAPPER_H

#include <map>

#include <network/Connection.h>

namespace core {

/**
 * The network mapper keeps a map op connection session ids with the linked machine id. This class is inherited by the
 * network connection handlers in production control, so when a message is received on a connection it can figure out
 * machine id.
 */
class NetworkMapper {
 public:
  NetworkMapper() = default;
  virtual ~NetworkMapper() = default;

 protected:
  /**
   * Set connection / machine id pair. (should be called in machine register received for example)
   * @param connection : connection to machine
   * @param machineId : machine id
   */
  void registerMachineConnection(const Network::ConnectionPtr& connection, uint16_t machineId);

  /**
   * removes connection / machine pair from the map
   * @param connection : connection to remove
   */
  void disconnectMachineConnection(const Network::ConnectionPtr& connection);

  /**
   * get the machine id of a connection. throws error if connection is not known! (should've registered machine, dummy!)
   * @param connection : connection to get the machine id from
   * @return : machine id
   */
  uint16_t getMachineIdForConnection(const Network::ConnectionPtr& connection) const;

 private:
  // map with connection session id, machine id
  std::map<uint32_t, uint16_t> machineConnectionMap;
};

}

#endif //PRODUCTION_LINE_CONTROL_NETWORKMAPPER_H
