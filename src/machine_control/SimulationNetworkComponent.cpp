//
// Created by hqnders on 20/04/18.
//

#include <iostream>
#include "SimulationNetworkComponent.h"

namespace SimulationCommunication {


	void SimulationNetworkComponent::onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) {
		IConnectionHandler::onConnectionFailed(connection, error);
	}

	void SimulationNetworkComponent::onConnectionEstablished(Network::ConnectionPtr connection) {
		mConnection = connection;
	}

	void SimulationNetworkComponent::onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) {
		std::cout << "dc" << std::endl;

	}

	void SimulationNetworkComponent::onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) {
		std::cout << message.mBody << std::endl;
	}

	void SimulationNetworkComponent::handleProcessProductMessage() {

	}

	void SimulationNetworkComponent::handleReconfigureMessage() {

	}

	void SimulationNetworkComponent::onConfigurationReceived(const std::string serializedConfigurations) {
		// TODO: Deserialize, notify observer
		
	}

	Network::ConnectionPtr SimulationNetworkComponent::getConnection() {
		return mConnection;
	}
}