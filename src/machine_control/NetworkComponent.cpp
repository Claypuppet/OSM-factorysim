//
// Created by klei on 4/19/18.
//

#include <iostream>
#include "NetworkComponent.h"

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
  std::cout << message.mBody << std::endl;
}

void NetworkComponent::handleProcessProductMessage() {

}

void NetworkComponent::handleReconfigureMessage() {

}

void NetworkComponent::sendRegisterMessage(const uint16_t machineId) {
  Network::Message message(Network::Protocol::AppMessageType::kAppMessageTypeRegisterMachine, std::to_string(machineId));
  mConnection->writeMessage(message);
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

}