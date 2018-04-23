//
// Created by don on 19-4-18.
//

#include "AppConnectionHandler.h"
#include "Machine.h"

#include <iostream>

/**
 * A handler for when a connection fails
 * @param connection
 * @param error
 */

void AppConnectionHandler::onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) {
    IConnectionHandler::onConnectionFailed(connection, error);
    std::cout << "Connection failed!" << std::endl;
}

/**
 * A handler for when a connection is established
 * @param connection
 */

void AppConnectionHandler::onConnectionEstablished(network::ConnectionPtr connection) {
    connection = connection;
}

/**
 * A handler for when a connection disconnects
 * @param connection
 * @param error
 */

void AppConnectionHandler::onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) {
    std::cout << "Disconnected!" << std::endl;
}

/**
 * A handler for when a message is received
 * @param connection
 * @param message
 */

void AppConnectionHandler::onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) {
    std::cout << "Received a message!" << std::endl;
    if(message.getMessageType() == 5)
    {
        uint8_t machineId = stoi(message.getBody());
        MachinePtr machine = app->getMachine(machineId);
        if(machine)
        {
            machine->setConnection(connection);
        }
        else {
            Machine m(machineId);
            m.setConnection(connection);
            app->addMachine(m);
        }
    }
}

/**
 * A handler for when a message is sent
 * @param connection
 * @param message
 */

void AppConnectionHandler::onConnectionMessageSent(network::ConnectionPtr connection, network::Message &message) {
    IConnectionHandler::onConnectionMessageSent(connection, message);
    std::cout << "Message sent!" << std::endl;
}

/**
 * The constructor
 * @param app
 */

AppConnectionHandler::AppConnectionHandler(Application *app) {
    this->app = app;
}
