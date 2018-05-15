//
// Created by klei on 4/19/18.
//

#include <iostream>
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
  std::cout << "dc" << std::endl;
}

void NetworkComponent::onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) {
  switch(message.getMessageType())
  {
    case Network::Protocol::kAppMessageTypeStartProcess:
      handleProcessProductMessage();
      break;
    default:
      break;
  }
}

void NetworkComponent::handleProcessProductMessage() {
  patterns::NotifyObserver::NotifyEvent notification(machinecore::NotifyEventType::kNotifyEventTypeStartProcess);
  notifyObservers(notification);
}

void NetworkComponent::handleReconfigureMessage() {

}

void NetworkComponent::sendRegisterMessage(const uint16_t machineId) {
  Network::Message
      message(Network::Protocol::AppMessageType::kAppMessageTypeRegisterMachine, std::to_string(machineId));
  mConnection->writeMessage(message);
}

}