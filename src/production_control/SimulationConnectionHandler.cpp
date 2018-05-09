//
// Created by sven on 25-4-18.
//

#include <network/Protocol.h>
#include <cereal/archives/portable_binary.hpp>
#include "SimulationConnectionHandler.h"
#include "NotificationTypes.h"

namespace Simulation {
void SimulationConnectionHandler::onConnectionFailed(Network::ConnectionPtr connection,
                                                     const boost::system::error_code &error) {
  IConnectionHandler::onConnectionFailed(connection, error);
  std::cout << "not connected" << std::endl;
}

void SimulationConnectionHandler::onConnectionEstablished(Network::ConnectionPtr connection) {
  mConnection = connection;
}

void SimulationConnectionHandler::onConnectionDisconnected(Network::ConnectionPtr connection,
                                                           const boost::system::error_code &error) {
  std::cout << "dc" << std::endl;
  std::cout << "not connected 2" << std::endl;

}

void SimulationConnectionHandler::onConnectionMessageReceived(Network::ConnectionPtr connection,
                                                              Network::Message &message) {
  std::cout << message.mBody << std::endl;
  switch (message.getMessageType()) {
    case Network::Protocol::kSimMessageTypeRegister:handleRegisterMachine(message.getBody(), connection);
      break;
    default:break;
  }
}

bool SimulationConnectionHandler::deserializeSimulationMachineInfo(const std::string &string,
                                                                   Models::MachinePtr machine) {
//		std::stringstream binaryStream((std::ios::in | std::ios::binary));
//		binaryStream.str(string);
//		cereal::PortableBinaryInputArchive archive(binaryStream);
//		archive(machine);
  return !!machine;
}

void SimulationConnectionHandler::onSimulationMachineInfoReceived(const Models::Machine &machine) {
//		auto machinePtr = std::make_shared<Model::Machine>(machine);


}

void SimulationConnectionHandler::handleRegisterMachine(const std::string &messageBody, Network::ConnectionPtr connection) {
  Patterns::NotifyObserver::NotifyEvent notification(NotifyEventIds::SimulationNotificationTypes::eSimRegisterMachine);
  notification.setArgument(0, static_cast<uint16_t >(std::stoi(messageBody, nullptr)));
  notification.setArgument(1, connection);
  notifyObservers(notification);
}

}