
// standard libraries
#include <iostream>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/vector.hpp>

// libraries
#include <network/Protocol.h>

// other
#include "SimulationNetworkComponent.h"
#include "ControllerNotificationEventIds.h"

namespace SimulationCommunication {

void SimulationNetworkComponent::onConnectionFailed(Network::ConnectionPtr connection,
                                                    const boost::system::error_code &error) {
  IConnectionHandler::onConnectionFailed(connection, error);
  std::cout << "not connected" << std::endl;
}

void SimulationNetworkComponent::onConnectionEstablished(Network::ConnectionPtr connection) {
  mConnection = connection;
}

void SimulationNetworkComponent::onConnectionDisconnected(Network::ConnectionPtr connection,
                                                          const boost::system::error_code &error) {
  std::cout << "dc" << std::endl;
  std::cout << "not connected 2" << std::endl;
}

void SimulationNetworkComponent::onConnectionMessageReceived(Network::ConnectionPtr connection,
                                                             Network::Message &message) {
  switch (message.getMessageType()) {
    case Network::Protocol::kSimMessageTypeConfig : {
      auto machineInfo = message.getBodyObject<models::MachinePtr>();
      onSimulationMachineInfoReceived(machineInfo);
      break;
    }
    case Network::Protocol::kSimMessageTypeTurnOn : {
      onTurnOnReceived();
      break;
    }
    case Network::Protocol::kSimMessageTypeTurnOff : {
      onTurnOffReceived();
      break;
    }
    default : {
      break;
    }
  }
}

void SimulationNetworkComponent::onSimulationMachineInfoReceived(models::MachinePtr machinePtr) {
  auto event =
      makeNotifcation(patterns::NotifyObserver::NotifyTrigger(), ControllerEvents::kNotifyEventTypeMachineInfoReceived);
  event.addArgument(machinePtr);
  notifyObservers(event);
}

void SimulationNetworkComponent::onTurnOffReceived() {
  auto notification =
      makeNotifcation(patterns::NotifyObserver::NotifyTrigger(), ControllerEvents::kNotifyEventTypeTurnOffReceived);
  notifyObservers(notification);
}

void SimulationNetworkComponent::onTurnOnReceived() {
  auto notification =
      makeNotifcation(patterns::NotifyObserver::NotifyTrigger(), ControllerEvents::kNotifyEventTypeTurnOnReceived);
  notifyObservers(notification);
}
void SimulationNetworkComponent::sendRegisterMessage(const uint16_t machineId) {
  Network::Message message(Network::Protocol::SimMessageType::kSimMessageTypeRegister , std::to_string(machineId));
  sendMessage(message);
}
void SimulationNetworkComponent::sendMessage(const Network::Message &message) {
  if(mConnection) {
    mConnection->writeMessage(message);
  }
}
bool SimulationNetworkComponent::isConnected() {
  return mConnection != nullptr;
}

}
