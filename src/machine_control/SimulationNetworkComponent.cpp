//
// Created by hqnders on 20/04/18.
//

#include "SimulationNetworkComponent.h"

void Communication::SimulationNetworkComponent::onConnectionEstablished(Network::ConnectionPtr connection) {

}

void Communication::SimulationNetworkComponent::onConnectionDisconnected(Network::ConnectionPtr connection,
                                                                         const boost::system::error_code &error) {

}

void Communication::SimulationNetworkComponent::onConnectionMessageReceived(Network::ConnectionPtr connection,
                                                                            Network::Message &message) {

}
