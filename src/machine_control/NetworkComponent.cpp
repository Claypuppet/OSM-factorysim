//
// Created by klei on 4/19/18.
//

#include <iostream>
#include <models/Machine.h>
#include "NetworkComponent.h"
#include "Application.h"

namespace Communication {

NetworkComponent::NetworkComponent() {

}

void NetworkComponent::onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) {
  IConnectionHandler::onConnectionFailed(connection, error);
}

void NetworkComponent::onConnectionEstablished(Network::ConnectionPtr connection) {
  mConnection = connection;
}

void NetworkComponent::onConnectionDisconnected(Network::ConnectionPtr connection,
                                                const boost::system::error_code &error) {
}

void NetworkComponent::onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) {
  switch (message.getMessageType()) {
    case Network::Protocol::kAppMessageTypeReconfigure : {
      handleProcessReconfigureMessage(message);
      break;
    }
    case Network::Protocol::kAppMessageTypeStartProcess:handleProcessProductMessage();
      break;
    default:break;
  }
}

void NetworkComponent::handleProcessProductMessage() {
  patterns::NotifyObserver::NotifyEvent notification(machinecore::NotifyEventType::kNotifyEventTypeStartProcess);
  notifyObservers(notification);
}

void NetworkComponent::handleProcessReconfigureMessage(Network::Message &message) {
  auto event =
      makeNotifcation(patterns::NotifyObserver::NotifyTrigger(), machinecore::kNotifyEventTypeMachineConfigReceived
      );
  event.addArgument(&message);
  notifyObservers(event);
}

void NetworkComponent::handleReconfigureMessage() {

}

bool NetworkComponent::isConnected() {
  return !!mConnection;
}

void NetworkComponent::sendMessage(Network::Message &message) {
  if (isConnected()) {
    mConnection->writeMessage(message);
  }

}

void NetworkComponent::sendStatusUpdateDone() {
  Network::Message message(Network::Protocol::AppMessageType::kAppMessageTypeDoneProcessing);
  mConnection->writeMessage(message);
}

void NetworkComponent::sendStatusUpdateStarted() {
  Network::Message message(Network::Protocol::AppMessageType::kAppMessageTypeStartedProcessing);
  mConnection->writeMessage(message);
}

void NetworkComponent::sendStatusUpdateReady() {
  Network::Message message(Network::Protocol::AppMessageType::kAppMessageTypeReady);
  mConnection->writeMessage(message);
}

void NetworkComponent::sendResponseNOK(const uint16_t errorCode) {
  Network::Message message(Network::Protocol::AppMessageType::kAppMessageTypeNOK, std::to_string(errorCode));
  mConnection->writeMessage(message);
}

void NetworkComponent::sendResponseOK() {
  Network::Message message(Network::Protocol::AppMessageType::kAppMessageTypeOK);
  mConnection->writeMessage(message);
}

void NetworkComponent::sendRegisterMachineMessage(uint16_t machineId) {
  Network::Message message(Network::Protocol::kAppMessageTypeRegisterMachine);
  message.setBody(std::to_string(machineId));
  sendMessage(message);

}

}