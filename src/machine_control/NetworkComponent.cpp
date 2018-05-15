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
  std::cout << "dc" << std::endl;
}

void NetworkComponent::onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) {
  std::cout << message.mBody << std::endl;
  switch (message.getMessageType()) {
    case Network::Protocol::kAppMessageTypeReconfigure : {
      auto event =
          makeNotifcation(patterns::NotifyObserver::NotifyTrigger(), machinecore::kNotifyEventTypeMachineConfigReceived
          );
      event.addArgument(&message);
      notifyObservers(event);
      break;
    }
    default : {
      break;
    }
  }
}

void NetworkComponent::handleProcessProductMessage() {

}

void NetworkComponent::handleReconfigureMessage() {

}

Network::ConnectionPtr NetworkComponent::getConnection() {
  return mConnection;
}

bool NetworkComponent::isConnected() {
  return !!mConnection;
}

void NetworkComponent::sendMessage(Network::Message &msg) {
  if (isConnected()) {
    mConnection->writeMessage(msg);
  }
}

void NetworkComponent::sendRegisterMachineMessage(uint16_t machineId) {
  Network::Message message(Network::Protocol::kAppMessageTypeRegisterMachine);
  message.setBody<models::Machine>(machineId);
  sendMessage(message);

}

}
