//
// Created by don on 20-4-18.
//

#include "Machine.h"

bool Core::Machine::isConnected() {
    if(connection != nullptr){
        return true;
    }
    return false;
}

void Core::Machine::sendMessage(Network::Message &msg) {
    connection->writeMessage(msg);
}

Core::Machine::Machine(Models::Machine aMachine)
    :Models::Machine(aMachine),connection(nullptr)
{

}

Core::Machine::Machine(const Machine &aMachine)
{

}

Core::Machine& Core::Machine::operator=(const Machine& rhs) {
    if(this != &rhs)
    {
        Models::Machine::operator=(rhs);
        connection = rhs.connection;
    }
    return *this;
}

void Core::Machine::setConnection(Network::ConnectionPtr aConnection) {
    connection = aConnection;
}
