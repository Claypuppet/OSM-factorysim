//
// Created by don on 20-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_MACHINE_H
#define PRODUCTION_LINE_CONTROL_MACHINE_H


#include <cstdint>
#include <network/Connection.h>

namespace Core {
    class Machine {
    public:
        /**
        * Constructor
        * @param anId The id of the machine
        */
        Machine(uint8_t anId);

        /**
        * Copy constructor
        * @param aMachine The machine to copy
        */
        Machine(const Machine &aMachine);

        /**
        * Assignment operator
        * @param rhs The machine to copy
        * @return The new machine
        */
        Machine &operator=(const Machine &rhs);

        ~Machine() = default;

        /**
        * A function to send a message to this machine
        * @param msg The message to send to this machine
        */
        void sendMessage(Network::Message &msg);

        /**
        * A function to check if a connection is established with the machine
        * @return True if theres a connection establised with the machine
        */
        bool isConnected();

        /**
        * A function that sets the connection with this machine
        * @param aConnection The connection with this machine
        */
        void setConnection(Network::ConnectionPtr aConnection);

        /**
        * A function to get the id of the machine
        * @return The id of the machine
        */
        uint8_t getId();

    private:
        uint8_t id;
        Network::ConnectionPtr connection;
    };

    typedef std::shared_ptr<Machine> MachinePtr;
}


#endif //PRODUCTION_LINE_CONTROL_MACHINE_H
