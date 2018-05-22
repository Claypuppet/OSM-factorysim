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
  event.addArgument<uint16_t>(message.getBodyObject<uint16_t>());
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

void NetworkComponent::sendStatusUpdate(models::Machine::MachineStatus status) {
  Network::Message message(Network::Protocol::AppMessageType::kAppMessageTypeOK);
  message.setBodyObject<models::Machine::MachineStatus >(status);
  mConnection->writeMessage(message);

}

void NetworkComponent::sendResponseNOK(const uint16_t errorCode) {
  Network::Message message(Network::Protocol::AppMessageType::kAppMessageTypeNOK);
  message.setBodyObject<uint16_t>(errorCode);
  mConnection->writeMessage(message);
}

void NetworkComponent::sendRegisterMachineMessage(uint16_t machineId) {
  Network::Message message(Network::Protocol::kAppMessageTypeRegisterMachine);
  message.setBodyObject<uint16_t>(machineId);
  sendMessage(message);

}

}