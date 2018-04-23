//
// Created by don on 19-4-18.
//

#include "CommNet.h"
#include "Machine.h"

#include <iostream>

/**
 * A handler for when a connection fails
 * @param connection
 * @param error
 */

void CommNet::onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) {
    IConnectionHandler::onConnectionFailed(connection, error);
    std::cout << "Connection failed!" << std::endl;
}

/**
 * A handler for when a connection is established
 * @param connection
 */

void CommNet::onConnectionEstablished(network::ConnectionPtr connection) {
    connection = connection;
}

/**
 * A handler for when a connection disconnects
 * @param connection
 * @param error
 */

void CommNet::onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) {
    std::cout << "Disconnected!" << std::endl;
}

/**
 * A handler for when a message is received
 * @param connection
 * @param message
 */

void CommNet::onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) {
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

void CommNet::onConnectionMessageSent(network::ConnectionPtr connection, network::Message &message) {
    IConnectionHandler::onConnectionMessageSent(connection, message);
    std::cout << "Message sent!" << std::endl;
}

/**
 * The constructor
 * @param app
 */

CommNet::CommNet(Application *app) {
    this->app = app;
}
