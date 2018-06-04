//
// Created by sven on 25-4-18.
//

#include <network/Protocol.h>
#include "SimulationConnectionHandler.h"
#include "NotificationTypes.h"

namespace simulationcommunication {

void SimulationConnectionHandler::onConnectionFailed(network::ConnectionPtr connection,
													 const boost::system::error_code &error) {
  IConnectionHandler::onConnectionFailed(connection, error);
}

void SimulationConnectionHandler::onConnectionEstablished(network::ConnectionPtr connection) {
  // No implementation needed, machine should register for connection to be used.
}

void SimulationConnectionHandler::onConnectionDisconnected(network::ConnectionPtr connection,
														   const boost::system::error_code &error) {
  disconnectMachineConnection(connection);
}

void SimulationConnectionHandler::onConnectionMessageReceived(network::ConnectionPtr connection,
															  network::Message &message) {
  switch (message.getMessageType()) {
	case network::Protocol::kSimMessageTypeRegister:
	  onHandleRegisterMachine(message, connection);
	  break;
	case network::Protocol::kSimMessageTypeReadyForSim:
	  handleMachineReady(connection);
	  break;
	default:
	  break;
  }
}

void SimulationConnectionHandler::handleMachineReady(network::ConnectionPtr connection) {
  auto machineId = getMachineIdForConnection(connection);
  auto notification = makeNotifcation(NotifyEventIds::eSimMachineReady);
  notification.setArgument(0, machineId);
  notifyObservers(notification);
}

void SimulationConnectionHandler::onHandleRegisterMachine(network::Message &message,
														  network::ConnectionPtr connection) {
  auto notification = makeNotifcation(patterns::notifyobserver::NotifyTrigger(),
									  NotifyEventIds::eSimRegisterMachine);

  uint16_t machineId = message.getBodyObject<uint16_t>();
  notification.setArgument(0, machineId);
  notification.setArgument(1, connection);

  // Register the machine as connection in this component
  registerMachineConnection(connection, machineId);

  notifyObservers(notification);
}

}