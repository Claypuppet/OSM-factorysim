//
// Created by sven on 25-4-18.
//

#include <network/Protocol.h>
#include "SimulationConnectionHandler.h"
#include "NotificationTypes.h"

namespace simulation {

void SimulationConnectionHandler::onConnectionFailed(Network::ConnectionPtr connection,
                                                     const boost::system::error_code &error) {
  IConnectionHandler::onConnectionFailed(connection, error);
}

void SimulationConnectionHandler::onConnectionEstablished(Network::ConnectionPtr connection) {
  // No implementation needed, machine should register for connection to be used.
}

void SimulationConnectionHandler::onConnectionDisconnected(Network::ConnectionPtr connection,
                                                           const boost::system::error_code &error) {

}

void SimulationConnectionHandler::onConnectionMessageReceived(Network::ConnectionPtr connection,
                                                              Network::Message &message) {
  switch (message.getMessageType()) {
    case Network::Protocol::kSimMessageTypeRegister: 
      onHandleRegisterMachine(message, connection);
      break;
    case Network::Protocol::kSimMessageTypeReadyForSim: 
      handleMachineReady(connection);
      break;
    default: break;
  }
}

void SimulationConnectionHandler::handleMachineReady(Network::ConnectionPtr connection) {
  auto machineId = getMachineIdForConnection(connection);
  auto notification = makeNotifcation(NotifyEventIds::eSimMachineReady);
  notification.setArgument(0, machineId);
  notifyObservers(notification);
}

void SimulationConnectionHandler::onHandleRegisterMachine(Network::Message &message,
                                                          Network::ConnectionPtr connection) {
  auto notification = makeNotifcation(patterns::NotifyObserver::NotifyTrigger(),
                                      NotifyEventIds::eSimRegisterMachine);

  uint16_t machineId = message.getBodyObject<uint16_t>();
  notification.setArgument(0, machineId);
  notification.setArgument(1, connection);

  // Register the machine as connection in this component
  registerMachineConnection(connection, machineId);

  notifyObservers(notification);
}

}