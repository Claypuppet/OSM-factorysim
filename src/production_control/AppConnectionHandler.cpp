//
// Created by don on 19-4-18.
//

#include "AppConnectionHandler.h"
#include "network/Protocol.h"
#include "NotificationTypes.h"

core::AppConnectionHandler::AppConnectionHandler() {}

void core::AppConnectionHandler::onConnectionFailed(Network::ConnectionPtr connection,
                                                    const boost::system::error_code &error) {
  Network::IConnectionHandler::onConnectionFailed(connection, error);
}

void core::AppConnectionHandler::onConnectionEstablished(Network::ConnectionPtr connection) {
}

void core::AppConnectionHandler::onConnectionDisconnected(Network::ConnectionPtr connection,
                                                          const boost::system::error_code &error) {
}

void core::AppConnectionHandler::onConnectionMessageReceived(Network::ConnectionPtr connection,
                                                             Network::Message &message) {
  uint8_t messageType = message.getMessageType();
  switch (messageType) {
    case Network::Protocol::kAppMessageTypeRegisterMachine:
      handleRegisterMachine(connection, message);
      break;
    case Network::Protocol::kAppMessageTypeInitialConfigure:
      handleStartInit(connection);
      break;
    case Network::Protocol::kAppMessageTypeOK:
      handleOK(connection);
      break;
    case Network::Protocol::kAppMessageTypeNOK:
      handleNOK(connection, message.getBody());
      break;
    case Network::Protocol::kAppMessageTypeDoneProcessing:
      handleDoneProcessing(connection);
      break;
    case Network::Protocol::kAppMessageTypeStartedProcessing:
      handleStartProcessing(connection);
      break;
    case Network::Protocol::kAppMessageTypeReady:
      handleMachineReady(connection);
      break;
    default:break;
  }
}

void core::AppConnectionHandler::onConnectionMessageSent(Network::ConnectionPtr connection, Network::Message &message) {
  Network::IConnectionHandler::onConnectionMessageSent(connection, message);
}

void core::AppConnectionHandler::handleRegisterMachine(Network::ConnectionPtr connection, Network::Message &message) {
  auto notification =
      makeNotifcation(patterns::NotifyObserver::NotifyTrigger(), NotifyEventIds::eApplicationRegisterMachine);
  auto machineId = static_cast<uint16_t >(std::strtoul(message.getBody().c_str(), nullptr, 10));

  registerMachineConnection(connection, machineId);

  notification.setArgument(0, machineId);
  notification.setArgument(1, connection);

  notifyObservers(notification);
}

void core::AppConnectionHandler::handleMachineReady(Network::ConnectionPtr connection) {
  auto notification =
      makeNotifcation(patterns::NotifyObserver::NotifyTrigger(), NotifyEventIds::eApplicationMachineReady);
  auto machineId = getMachineIdForConnection(connection);

  notification.setArgument(0, machineId);

  notifyObservers(notification);
}

void core::AppConnectionHandler::handleStartInit(Network::ConnectionPtr connection) {
  auto notification = makeNotifcation(patterns::NotifyObserver::NotifyTrigger(), NotifyEventIds::eApplicationStartInit);
  auto machineId = getMachineIdForConnection(connection);

  notification.setArgument(0, machineId);

  notifyObservers(notification);
}

void core::AppConnectionHandler::handleStartProcessing(Network::ConnectionPtr connection) {
  auto notification =
      makeNotifcation(patterns::NotifyObserver::NotifyTrigger(), NotifyEventIds::eApplicationStartProcessing);
  auto machineId = getMachineIdForConnection(connection);

  notification.setArgument(0, machineId);

  notifyObservers(notification);
}

void core::AppConnectionHandler::handleDoneProcessing(Network::ConnectionPtr connection) {
  auto notification =
      makeNotifcation(patterns::NotifyObserver::NotifyTrigger(), NotifyEventIds::eApplicationDoneProcessing);
  auto machineId = getMachineIdForConnection(connection);

  notification.setArgument(0, machineId);

  notifyObservers(notification);
}

void core::AppConnectionHandler::handleOK(Network::ConnectionPtr connection) {
  auto notification = makeNotifcation(patterns::NotifyObserver::NotifyTrigger(), NotifyEventIds::eApplicationOK);
  auto machineId = getMachineIdForConnection(connection);

  notification.setArgument(0, machineId);

  notifyObservers(notification);
}

void core::AppConnectionHandler::handleNOK(Network::ConnectionPtr connection, std::string messageBody) {
  auto notification = makeNotifcation(patterns::NotifyObserver::NotifyTrigger(), NotifyEventIds::eApplicationNOK);
  auto machineId = getMachineIdForConnection(connection);

  notification.setArgument(0, machineId);
  notification.setArgument(1, messageBody);

  notifyObservers(notification);
}
