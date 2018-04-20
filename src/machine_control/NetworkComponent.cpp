//
// Created by klei on 4/19/18.
//

#include <iostream>
#include "NetworkComponent.h"

void NetworkComponent::onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) {
	IConnectionHandler::onConnectionFailed(connection, error);
	std::cout << "fail" << std::endl;
}

void NetworkComponent::onConnectionEstablished(network::ConnectionPtr connection) {
	mConnection = connection;
}

void NetworkComponent::onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) {
	std::cout << "dc" << std::endl;
}

void NetworkComponent::onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) {
	std::cout << message.mBody << std::endl;
}

void NetworkComponent::handleProcessProductMessage() {

}

void NetworkComponent::handleReconfigureMessage() {

}

const void NetworkComponent::sendHello() {
	network::Message msg(1, "aaaaa");
	mConnection->writeMessage(msg);
}

network::ConnectionPtr NetworkComponent::getConnection() {
	return mConnection;
}
