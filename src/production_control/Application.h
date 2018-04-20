//
// Created by don on 20-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_APPLICATION_H
#define PRODUCTION_LINE_CONTROL_APPLICATION_H


#include "Machine.h"
#include "network/Manager.h"

class Application {
public:
    Application();
    ~Application() = default;
    void addMachine(const Machine& aMachine);
    MachinePtr getMachine(uint8_t machineId);
    void joinServerThread();
    void joinClientThread();
private:
    std::vector<Machine> machines;
    network::ServerPtr server;
    network::ClientPtr client;
    ThreadPtr clientThread;
    ThreadPtr serverThread;
};


#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
