//
// Created by don on 20-4-18.
//

#include "Machine.h"

uint8_t Core::Machine::getId() {
    return id;
}

bool Core::Machine::isConnected() {
    if(connection != nullptr){
        return true;
    }
    return false;
}

void Core::Machine::sendMessage(Network::Message &msg) {
    connection->writeMessage(msg);
}

Core::Machine::Machine(uint8_t anId)
    :id(anId),connection(nullptr)
{

}

Core::Machine::Machine(const Machine &aMachine)
    :id(aMachine.id),connection(aMachine.connection)
{

}

Core::Machine& Core::Machine::operator=(const Machine& rhs) {
    if(this != &rhs)
    {
        id = rhs.id;
        connection = rhs.connection;
    }
    return *this;
}

void Core::Machine::setConnection(Network::ConnectionPtr aConnection) {
    connection = aConnection;
}
