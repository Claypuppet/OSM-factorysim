//
// Created by klei on 4/19/18.
//

#include "NetworkComponent.h"

void NetworkComponent::onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) {
	IConnectionHandler::onConnectionFailed(connection, error);
}

void NetworkComponent::onConnectionEstablished(network::ConnectionPtr connection) {

}

void
NetworkComponent::onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) {

}

void NetworkComponent::onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) {

}

void NetworkComponent::onConnectionMessageSent(network::ConnectionPtr connection, network::Message &message) {
	IConnectionHandler::onConnectionMessageSent(connection, message);
}
