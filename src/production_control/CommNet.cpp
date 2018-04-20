//
// Created by don on 19-4-18.
//

#include "CommNet.h"
#include "Machine.h"

#include <iostream>

void CommNet::onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) {
    IConnectionHandler::onConnectionFailed(connection, error);
    std::cout << "Connection failed!" << std::endl;
}

void CommNet::onConnectionEstablished(network::ConnectionPtr connection) {
    connection = connection;
}

void CommNet::onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) {
    std::cout << "Disconnected!" << std::endl;
}

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

void CommNet::onConnectionMessageSent(network::ConnectionPtr connection, network::Message &message) {
    IConnectionHandler::onConnectionMessageSent(connection, message);
    std::cout << "Message sent!" << std::endl;
}

CommNet::CommNet(Application *app) {
    this->app = app;
}
