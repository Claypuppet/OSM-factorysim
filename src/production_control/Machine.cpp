//
// Created by don on 20-4-18.
//

#include "Machine.h"

/**
 * A function to get the id of the machine
 * @return The id of the machine
 */

uint8_t Machine::getId() {
    return id;
}

/**
 * A function to check if a connection is established with the machine
 * @return True if theres a connection establised with the machine
 */

bool Machine::isConnected() {
    if(connection){
        return true;
    }
    return false;
}

/**
 * A function to send a message to this machine
 * @param msg The message to send to this machine
 */

void Machine::sendMessage(network::Message &msg) {
    connection->writeMessage(msg);
}

/**
 * Constructor
 * @param anId The id of the machine
 */

Machine::Machine(uint8_t anId)
    :id(anId)
{

}

/**
 * Copy constructor
 * @param aMachine The machine to copy
 */

Machine::Machine(const Machine &aMachine)
    :id(aMachine.id),connection(aMachine.connection)
{

}

/**
 * Assignment operator
 * @param rhs The machine to copy
 * @return The new machine
 */

Machine& Machine::operator=(const Machine& rhs) {
    if(this != &rhs)
    {
        id = rhs.id;
        connection = rhs.connection;
    }
    return *this;
}

/**
 * A function that sets the connection with this machine
 * @param aConnection The connection with this machine
 */

void Machine::setConnection(network::ConnectionPtr aConnection) {
    connection = aConnection;
}
