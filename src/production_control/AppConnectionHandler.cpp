//
// Created by don on 19-4-18.
//

#include "AppConnectionHandler.h"
#include "Machine.h"
#include "network/Protocol.h"

#include <iostream>

/**
 * A handler for when a connection fails
 * @param connection
 * @param error
 */

void AppConnectionHandler::onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) {
    Network::IConnectionHandler::onConnectionFailed(connection, error);
    std::cout << "Connection failed!" << std::endl;
}

/**
 * A handler for when a connection is established
 * @param connection
 */

void AppConnectionHandler::onConnectionEstablished(Network::ConnectionPtr connection) {
    //std::cout << "test" << std::endl;
}

/**
 * A handler for when a connection disconnects
 * @param connection
 * @param error
 */

void AppConnectionHandler::onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) {
    std::cout << "Disconnected!" << std::endl;
}

/**
 * A handler for when a message is received
 * @param connection
 * @param message
 */

void AppConnectionHandler::onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) {
    std::cout << "Received a message!" << std::endl;
    if(message.getMessageType() == Network::Protocol::kAppMessageTypeRegisterMachine)
    {
        uint8_t machineId = stoi(message.getBody());
        MachinePtr machine = app->getMachine(machineId);
        if(machine)
        {
            machine->setConnection(connection);
            std::cout << "Added connection to machine with ID: " << machineId << std::endl;
        }
        else {
            Machine m(machineId);
            m.setConnection(connection);
            app->addMachine(m);
            std::cout << "Added machine with ID: " << machineId << std::endl;
        }
    }
}

/**
 * A handler for when a message is sent
 * @param connection
 * @param message
 */

void AppConnectionHandler::onConnectionMessageSent(Network::ConnectionPtr connection, Network::Message &message) {
    Network::IConnectionHandler::onConnectionMessageSent(connection, message);
    std::cout << "Message sent!" << std::endl;
}

/**
 * The constructor
 * @param app
 */

AppConnectionHandler::AppConnectionHandler(Application *app) {
    this->app = app;
}
