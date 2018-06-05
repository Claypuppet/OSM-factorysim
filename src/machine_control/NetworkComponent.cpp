//
// Created by klei on 4/19/18.
//

#include <iostream>
#include <models/Machine.h>
#include <utils/time/Time.h>
#include "NetworkComponent.h"
#include "Application.h"

namespace Communication {

NetworkComponent::NetworkComponent() {

}

void NetworkComponent::onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) {
  IConnectionHandler::onConnectionFailed(connection, error);
}

void NetworkComponent::onConnectionEstablished(network::ConnectionPtr connection) {
  mConnection = connection;
}

void NetworkComponent::onConnectionDisconnected(network::ConnectionPtr connection,
												const boost::system::error_code &error) {
}

void NetworkComponent::onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) {
  utils::Time::getInstance().syncTime(message.getTime());
  switch (message.getMessageType()) {
	case network::Protocol::kAppMessageTypeReconfigure : {
      handleReconfigureMessage(message);
	  break;
	}
	case network::Protocol::kAppMessageTypeStartProcess:
	  handleProcessProductMessage();
	  break;
	default:
	  break;
  }
}

void NetworkComponent::handleProcessProductMessage() {
  patterns::notifyobserver::NotifyEvent notification(machinecore::NotifyEventType::kNotifyEventTypeStartProcess);
  notifyObservers(notification);
}

void NetworkComponent::handleReconfigureMessage(network::Message &message) {
  auto event =
	  makeNotifcation(patterns::notifyobserver::NotifyTrigger(), machinecore::NotifyEventType::kNotifyEventTypeConfigure
	  );
  event.addArgument<uint16_t>(message.getBodyObject<uint16_t>());
  notifyObservers(event);
}

bool NetworkComponent::isConnected() {
  return !!mConnection;
}

void NetworkComponent::sendMessage(network::Message &message) {
  message.setTime(utils::Time::getInstance().getCurrentTime());
  if (isConnected()) {
	mConnection->writeMessage(message);
  }
}

void NetworkComponent::sendStatusUpdate(models::Machine::MachineStatus status) {
  network::Message message(network::Protocol::AppMessageType::kAppMessageTypeOK);
  message.setBodyObject<models::Machine::MachineStatus>(status);
  sendMessage(message);

}

void NetworkComponent::sendResponseNOK(models::Machine::MachineErrorCode errorCode) {
  network::Message message(network::Protocol::AppMessageType::kAppMessageTypeNOK);
  message.setBodyObject<models::Machine::MachineErrorCode>(errorCode);
  sendMessage(message);
}

void NetworkComponent::sendRegisterMachineMessage(uint16_t machineId) {
  network::Message message(network::Protocol::kAppMessageTypeRegisterMachine);
  message.setBodyObject<uint16_t>(machineId);
  sendMessage(message);
}

void NetworkComponent::sendProductTakenFromBufferMessage() {
  network::Message message(network::Protocol::AppMessageType::kAppMessageTypeProductTakenFromBuffer);
  sendMessage(message);
}

void NetworkComponent::sendProductAddedToBufferMessage() {
  network::Message message(network::Protocol::AppMessageType::kAppMessageTypeProductAddedToBuffer);
  sendMessage(message);
}

}