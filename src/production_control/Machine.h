//
// Created by don on 20-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_MACHINE_H
#define PRODUCTION_LINE_CONTROL_MACHINE_H


#include <cstdint>
#include <network/Connection.h>


class Machine {
public:
    Machine(uint8_t anId);
    Machine(const Machine& aMachine);
    Machine& operator=(const Machine& rhs);
    ~Machine() = default;
    void sendMessage(Network::Message& msg);
    bool isConnected();
    void setConnection(Network::ConnectionPtr aConnection);
    uint8_t getId();
private:
    uint8_t id;
    Network::ConnectionPtr connection;
};

typedef std::shared_ptr<Machine> MachinePtr;


#endif //PRODUCTION_LINE_CONTROL_MACHINE_H
