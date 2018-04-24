//
// Created by don on 23-4-18.
//

#include <Logger/Logger.h>
#include "TestConnectionHandler.h"

void
TestConnectionHandler::onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) {
    IConnectionHandler::onConnectionFailed(connection, error);
}

void TestConnectionHandler::onConnectionEstablished(Network::ConnectionPtr connection) {

}

void TestConnectionHandler::onConnectionDisconnected(Network::ConnectionPtr connection,
                                                     const boost::system::error_code &error) {

}

void TestConnectionHandler::onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) {
    Logger::log("Message received:");
    Logger::log(message.getBody());
    Logger::log("\n");
}

void TestConnectionHandler::onConnectionMessageSent(Network::ConnectionPtr connection, Network::Message &message) {
    IConnectionHandler::onConnectionMessageSent(connection, message);
}
