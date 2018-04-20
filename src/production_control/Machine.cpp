//
// Created by don on 20-4-18.
//

#include "Machine.h"

uint8_t Machine::getId() {
    return id;
}

bool Machine::isConnected() {
    if(connection){
        return true;
    }
    return false;
}

void Machine::sendMessage(network::Message &msg) {
    connection->writeMessage(msg);
}

Machine::Machine(uint8_t anId)
    :id(anId)
{

}

Machine::Machine(const Machine &aMachine)
    :id(aMachine.id),connection(aMachine.connection)
{

}

Machine& Machine::operator=(const Machine& rhs) {
    if(this != &rhs)
    {
        id = rhs.id;
        connection = rhs.connection;
    }
    return *this;
}

void Machine::setConnection(network::ConnectionPtr aConnection) {
    connection = aConnection;
}
