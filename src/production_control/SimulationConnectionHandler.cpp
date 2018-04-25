//
// Created by don on 25-4-18.
//

#include "SimulationConnectionHandler.h"

void
Core::SimulationConnectionHandler::handleConfigMessage(const std::string &msgBody, Network::ConnectionPtr connection) {

}

void Core::SimulationConnectionHandler::onConnectionMessageSent(Network::ConnectionPtr connection,
                                                                Network::Message &message) {
    IConnectionHandler::onConnectionMessageSent(connection, message);
}

void Core::SimulationConnectionHandler::onConnectionMessageReceived(Network::ConnectionPtr connection,
                                                                    Network::Message &message) {

}

void Core::SimulationConnectionHandler::onConnectionDisconnected(Network::ConnectionPtr connection,
                                                                 const boost::system::error_code &error) {

}

void Core::SimulationConnectionHandler::onConnectionEstablished(Network::ConnectionPtr connection) {

}

void Core::SimulationConnectionHandler::onConnectionFailed(Network::ConnectionPtr connection,
                                                           const boost::system::error_code &error) {
    IConnectionHandler::onConnectionFailed(connection, error);
}
