//
// Created by don on 19-4-18.
//

#include "AppConnectionHandler.h"
#include "network/Protocol.h"

/**
 * The constructor (Set temp application pointer till observer - notifier pattern implementation)
 * @param app
 */

Core::AppConnectionHandler::AppConnectionHandler() {}

/**
 * A handler for when a connection fails
 * @param connection
 * @param error
 */

void Core::AppConnectionHandler::onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) {
    Network::IConnectionHandler::onConnectionFailed(connection, error);
    std::cout << "Connection failed!" << std::endl;
}

/**
 * A handler for when a connection is established
 * @param connection
 */

void Core::AppConnectionHandler::onConnectionEstablished(Network::ConnectionPtr connection) {
    //std::cout << "test" << std::endl;
}

/**
 * A handler for when a connection disconnects
 * @param connection
 * @param error
 */

void Core::AppConnectionHandler::onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) {
    std::cout << "Disconnected!" << std::endl;
}

/**
 * A handler for when a message is received
 * @param connection
 * @param message
 */

void Core::AppConnectionHandler::onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) {
    std::cout << "Received a message!" << std::endl;
    uint8_t messageType = message.getMessageType();
    switch(messageType)
    {
        case Network::Protocol::kAppMessageTypeRegisterMachine:
            handleRegisterMachine(message.getBody(), connection);
            break;
    }
}

/**
 * A handler for when a message is sent
 * @param connection
 * @param message
 */

void Core::AppConnectionHandler::onConnectionMessageSent(Network::ConnectionPtr connection, Network::Message &message) {
    Network::IConnectionHandler::onConnectionMessageSent(connection, message);
    std::cout << "Message sent!" << std::endl;
}

void Core::AppConnectionHandler::handleRegisterMachine(const std::string &msgBody, Network::ConnectionPtr connection) {

}
