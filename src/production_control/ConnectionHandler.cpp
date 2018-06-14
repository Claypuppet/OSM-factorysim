//
// Created by don on 19-4-18.
//

#include <utils/Logger.h>
#include <utils/time/Time.h>
#include "ConnectionHandler.h"
#include "NotificationTypes.h"

namespace communication {

void ConnectionHandler::onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) {
  network::IConnectionHandler::onConnectionFailed(connection, error);
}

void ConnectionHandler::onConnectionEstablished(network::ConnectionPtr connection) {
}

void ConnectionHandler::onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) {
  try {
    auto machineId = getMachineIdForConnection(connection);
    auto notification = makeNotifcation(NotifyEventIds::eApplicationMachineDisconnected);

    notification.setArgument(0, utils::Time::getInstance().getCurrentTime());
    notification.setArgument(1, machineId);

    notifyObservers(notification);
  }
  catch (const std::exception &e) {
    utils::Logger::error("unknown machine disconnected...");
  }
  disconnectMachineConnection(connection);
}

void ConnectionHandler::onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) {
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
    case network::Protocol::kAppMessageTypeProductAddedToBuffer:
      handleProductAddedToBuffer(connection, message);
      break;
    case network::Protocol::kAppMessageTypeProductTakenFromBuffer:
      handleProductTakenFromBuffer(connection, message);
      break;
    default:
      break;
  }
}

void ConnectionHandler::onConnectionMessageSent(network::ConnectionPtr connection, network::Message &message) {
  network::IConnectionHandler::onConnectionMessageSent(connection, message);
}

void ConnectionHandler::handleRegisterMachine(network::ConnectionPtr connection, network::Message &message) {
  auto notification = makeNotifcation(NotifyEventIds::eApplicationRegisterMachine);
  auto machineId = message.getBodyObject<uint16_t>();

  registerMachineConnection(connection, machineId);

  notification.setArgument(0, message.getTime());
  notification.setArgument(1, machineId);
  notification.setArgument(2, connection);

  notifyObservers(notification);
}

void ConnectionHandler::handleOK(network::ConnectionPtr connection, network::Message &message) {
  auto notification = makeNotifcation(NotifyEventIds::eApplicationOK);
  auto machineId = getMachineIdForConnection(connection);

  notification.setArgument(0, message.getTime());
  notification.setArgument(1, machineId);
  notification.setArgument(2, message.getBodyObject<models::Machine::MachineStatus>());

  notifyObservers(notification);
}

void ConnectionHandler::handleNOK(network::ConnectionPtr connection, network::Message &message) {
  auto notification = makeNotifcation(NotifyEventIds::eApplicationNOK);
  auto machineId = getMachineIdForConnection(connection);

  notification.setArgument(0, message.getTime());
  notification.setArgument(1, machineId);
  notification.setArgument(2, message.getBodyObject<models::Machine::MachineErrorCode>());

  notifyObservers(notification);
}

void ConnectionHandler::handleProductAddedToBuffer(network::ConnectionPtr connection, network::Message &message) {
  auto machineId = getMachineIdForConnection(connection);
  auto notification = makeNotifcation(NotifyEventIds::eApplicationProductAddedToBuffer);

  notification.setArgument(0, message.getTime());
  notification.setArgument(1, machineId);

  notifyObservers(notification);
}

void ConnectionHandler::handleProductTakenFromBuffer(network::ConnectionPtr connection, network::Message &message) {
  auto machineId = getMachineIdForConnection(connection);
  auto notification = makeNotifcation(NotifyEventIds::eApplicationProductTakenFromBuffer);

  notification.setArgument(0, message.getTime());
  notification.setArgument(1, machineId);

  notifyObservers(notification);
}

}
