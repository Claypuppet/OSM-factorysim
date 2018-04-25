//
// Created by hqnders on 20/04/18.
//


#include <iostream>

#include <network/Protocol.h>

#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/vector.hpp>

#include "SimulationNetworkComponent.h"



namespace SimulationCommunication {


	void SimulationNetworkComponent::onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) {
		IConnectionHandler::onConnectionFailed(connection, error);
		std::cout << "not connected" << std::endl;
	}

	void SimulationNetworkComponent::onConnectionEstablished(Network::ConnectionPtr connection) {
		mConnection = connection;
	}

	void SimulationNetworkComponent::onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) {
		std::cout << "dc" << std::endl;
		std::cout << "not connected 2" << std::endl;

	}

	void SimulationNetworkComponent::onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) {
		std::cout << message.mBody << std::endl;
		switch(message.getMessageType()){
			case Network::Protocol::kSimMessageTypeConfig :
//				Model::MachinePtr machine;
//				if (deserializeSimulationMachineInfo(message.mBody, machine)){
//					onSimulationMachineInfoReceived(machine);
//				}
				break;
			case Network::Protocol::kSimMessageTypeTurnOn :
				onTurnOnReceived();
				break;
			case Network::Protocol::kSimMessageTypeTurnOff :
				onTurnOffReceived();
				break;
			default:
				break;
		}
	}

	bool SimulationNetworkComponent::deserializeSimulationMachineInfo(const std::string &string, Model::MachinePtr machine) {
//		std::stringstream binaryStream((std::ios::in | std::ios::binary));
//		binaryStream.str(string);
//		cereal::PortableBinaryInputArchive archive(binaryStream);
//		archive(machine);
		return !!machine;
	}

	void SimulationNetworkComponent::onSimulationMachineInfoReceived(const Model::Machine &machine) {
//		auto machinePtr = std::make_shared<Model::Machine>(machine);

		
	}

	void SimulationNetworkComponent::onTurnOffReceived() {

	}

	void SimulationNetworkComponent::onTurnOnReceived() {

	}
}