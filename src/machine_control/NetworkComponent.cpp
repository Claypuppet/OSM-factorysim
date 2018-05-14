//
// Created by klei on 4/19/18.
//

#include <iostream>
#include "NetworkComponent.h"
#include <network/Protocol.h>

namespace Communication {

NetworkComponent::NetworkComponent() {

}

void NetworkComponent::onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) {
  IConnectionHandler::onConnectionFailed(connection, error);
}

void NetworkComponent::onConnectionEstablished(Network::ConnectionPtr connection) {
  mConnection = connection;

  sendHello();
}

void NetworkComponent::onConnectionDisconnected(Network::ConnectionPtr connection,
                                                const boost::system::error_code &error) {
  std::cout << "dc" << std::endl;
}

void NetworkComponent::onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) {
  std::cout << message.mBody << std::endl;
}

void NetworkComponent::handleProcessProductMessage() {

}

void NetworkComponent::handleReconfigureMessage() {

}

const void NetworkComponent::sendHello() {
  Network::Message msg(1, "1");
  mConnection->writeMessage(msg);
}

void NetworkComponent::sendRegisterMessage(const uint16_t machineId) {
  Network::Message
      message(Network::Protocol::AppMessageType::kAppMessageTypeRegisterMachine, std::to_string(machineId));
  mConnection->writeMessage(message);
}

}