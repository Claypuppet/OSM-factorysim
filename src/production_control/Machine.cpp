//
// Created by don on 20-4-18.
//

#include "Machine.h"

namespace core {

    Machine::Machine(const Models::Machine &aMachine) :
            Models::Machine(aMachine)
    {

    }

    Machine::Machine(const Machine &aMachine) :
            Models::Machine(aMachine)
    {

    }

    Machine& Machine::operator=(const Machine& rhs) {
        if(this != &rhs)
        {
            Models::Machine::operator=(rhs);
            connection = rhs.connection;
        }
        return *this;
    }

    void Machine::setConnection(Network::ConnectionPtr aConnection) {
        connection = aConnection;
    }

    bool Machine::isConnected() {
        return !!connection;
    }

    void Machine::sendMessage(Network::Message &msg) {
        if(isConnected()){
            connection->writeMessage(msg);
        }
    }


}