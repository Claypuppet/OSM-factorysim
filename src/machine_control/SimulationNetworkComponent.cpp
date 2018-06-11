
// standard libraries
#include <iostream>
#include <cereal/archives/portable_binary.hpp>

// libraries
#include <network/Protocol.h>
#include <utils/time/Time.h>

// other
#include "SimulationNetworkComponent.h"
#include "NotificationEventTypes.h"

namespace simulationcommunication {

void SimulationNetworkComponent::onConnectionFailed(network::ConnectionPtr connection,
                                                    const boost::system::error_code &error) {
  IConnectionHandler::onConnectionFailed(connection, error);
}

void SimulationNetworkComponent::onConnectionEstablished(network::ConnectionPtr connection) {
  mConnection = connection;
}

void SimulationNetworkComponent::onConnectionDisconnected(network::ConnectionPtr connection,
                                                          const boost::system::error_code &error) {
  auto event = makeNotifcation(ControllerEvents::kNotifyEventTypeServiceStopped);
  if(error){
    notifyObservers(event);
  }
}

void SimulationNetworkComponent::onConnectionMessageReceived(network::ConnectionPtr connection,
                                                             network::Message &message) {
  switch (message.getMessageType()) {
    case network::Protocol::kSimMessageTypeConfig : {
      auto machineInfo = message.getBodyObject<models::MachinePtr>();
      onSimulationMachineInfoReceived(machineInfo);
      break;
    }
    case network::Protocol::kSimMessageTypeTurnOn : {
      onTurnOnReceived();
      break;
    }
    case network::Protocol::kSimMessageTypeTurnOff : {
      onTurnOffReceived();
      break;
    }
    default : {
      break;
    }
  }
}

void SimulationNetworkComponent::onSimulationMachineInfoReceived(models::MachinePtr machine) {
  auto notification =
      makeNotifcation(patterns::notifyobserver::NotifyTrigger(),
                      ControllerEvents::kNotifyEventTypeSimulationConfigurationsReceived);

  notification.addArgument(machine);
  notifyObservers(notification);
}

void SimulationNetworkComponent::onTurnOffReceived() {
  auto notification = makeNotifcation(ControllerEvents::kNotifyEventTypeTurnOffReceived);
  notifyObservers(notification);
}

void SimulationNetworkComponent::onTurnOnReceived() {
  auto notification = makeNotifcation(ControllerEvents::kNotifyEventTypeTurnOnReceived);
  notifyObservers(notification);
}

void SimulationNetworkComponent::sendRegisterMessage(const uint16_t machineId) {
  network::Message message(network::Protocol::SimMessageType::kSimMessageTypeRegister);
  message.setBodyObject<uint16_t>(machineId);
  sendMessage(message);
}

void SimulationNetworkComponent::sendMachineReadyMessage() {
  network::Message message(network::Protocol::SimMessageType::kSimMessageTypeReadyForSim);
  sendMessage(message);
}

void SimulationNetworkComponent::sendMessage(network::Message &message) {
  message.setTime(utils::Time::getInstance().getCurrentTime());
  if (mConnection) {
    mConnection->writeMessage(message);
  }
}

bool SimulationNetworkComponent::isConnected() {
  return mConnection != nullptr;
}
}
