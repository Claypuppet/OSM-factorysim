//
// Created by don on 19-4-18.
//

#include "ConnectionHandler.h"
#include "network/Protocol.h"
#include "NotificationTypes.h"

communication::ConnectionHandler::ConnectionHandler() {}

void communication::ConnectionHandler::onConnectionFailed(network::ConnectionPtr connection,
													const boost::system::error_code &error) {
  network::IConnectionHandler::onConnectionFailed(connection, error);
}

void communication::ConnectionHandler::onConnectionEstablished(network::ConnectionPtr connection) {
}

void communication::ConnectionHandler::onConnectionDisconnected(network::ConnectionPtr connection,
														  const boost::system::error_code &error) {
}

void communication::ConnectionHandler::onConnectionMessageReceived(network::ConnectionPtr connection,
															 network::Message &message) {
  uint8_t messageType = message.getMessageType();
  switch (messageType) {
	case network::Protocol::kAppMessageTypeRegisterMachine:
	  handleRegisterMachine(connection, message);
	  break;
	case network::Protocol::kAppMessageTypeOK:
	  handleOK(connection, message);
	  break;
	case network::Protocol::kAppMessageTypeNOK:
	  handleNOK(connection, message);
	  break;
	default:
	  break;
  }
}

void communication::ConnectionHandler::onConnectionMessageSent(network::ConnectionPtr connection, network::Message &message) {
  network::IConnectionHandler::onConnectionMessageSent(connection, message);
}

void communication::ConnectionHandler::handleRegisterMachine(network::ConnectionPtr connection, network::Message &message) {
  auto notification =
	  makeNotifcation(patterns::notifyobserver::NotifyTrigger(), NotifyEventIds::eApplicationRegisterMachine);
  auto machineId = message.getBodyObject<uint16_t>();

  registerMachineConnection(connection, machineId);

  notification.setArgument(0, machineId);
  notification.setArgument(1, connection);

  notifyObservers(notification);
}

void communication::ConnectionHandler::handleOK(network::ConnectionPtr connection, network::Message &message) {
  auto notification = makeNotifcation(patterns::notifyobserver::NotifyTrigger(), NotifyEventIds::eApplicationOK);
  auto machineId = getMachineIdForConnection(connection);

  notification.setArgument(0, machineId);
  notification.setArgument(1, message.getBodyObject<models::Machine::MachineStatus>());

  notifyObservers(notification);
}

void communication::ConnectionHandler::handleNOK(network::ConnectionPtr connection, network::Message &message) {
  auto notification = makeNotifcation(patterns::notifyobserver::NotifyTrigger(), NotifyEventIds::eApplicationNOK);
  auto machineId = getMachineIdForConnection(connection);

  notification.setArgument(0, machineId);
  notification.setArgument(1, message.getBodyObject<uint16_t>());

  notifyObservers(notification);
}
