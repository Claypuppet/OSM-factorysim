//
// Created by don on 20-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_APPLICATION_H
#define PRODUCTION_LINE_CONTROL_APPLICATION_H


#include "Machine.h"
#include "network/Manager.h"

class AppConnectionHandler;

class Application {
public:
    Application();
    ~Application() = default;
    void addMachine(const Machine& aMachine);
    MachinePtr getMachine(uint8_t machineId);
    void joinServerThread();
    bool isServerRunning();
    void startServer();
private:
    std::vector<Machine> machines;
    Network::ServerPtr server;
    ThreadPtr serverThread;
    std::shared_ptr<AppConnectionHandler> connectionHandler;
	Network::Manager m;
};


#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
