//
// Created by klei on 4/19/18.
//

#include <iostream>
#include "NetworkComponent.h"

namespace Communication {

	void NetworkComponent::onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) {
		IConnectionHandler::onConnectionFailed(connection, error);
	}

	void NetworkComponent::onConnectionEstablished(Network::ConnectionPtr connection) {
		mConnection = connection;
	}

	void NetworkComponent::onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) {
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
		Network::Message msg(1, "aaaaa");
		mConnection->writeMessage(msg);
	}

	Network::ConnectionPtr NetworkComponent::getConnection() {
		return mConnection;
	}
}
