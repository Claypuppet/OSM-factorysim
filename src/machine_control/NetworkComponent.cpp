//
// Created by hqnders on 20/04/18.
//

#include "NetworkComponent.h"

void Communication::NetworkComponent::onConnectionEstablished(Network::ConnectionPtr connection) {

}

void Communication::NetworkComponent::onConnectionDisconnected(Network::ConnectionPtr connection,
                                                               const boost::system::error_code &error) {

}

void Communication::NetworkComponent::onConnectionMessageReceived(Network::ConnectionPtr connection,
                                                                  Network::Message &message) {

}
