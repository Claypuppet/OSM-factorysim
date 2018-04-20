//
// Created by don on 20-4-18.
//

#include "Application.h"

#include "CommNet.h"
#include "network/Server.h"
#include "network/Client.h"

void Application::addMachine(const Machine &aMachine) {
    machines.push_back(aMachine);
}

MachinePtr Application::getMachine(uint8_t machineId) {
    for(Machine& m : machines)
    {
        if(m.getId() == machineId)
        {
            return std::make_shared<Machine>(m);
        }
    }
    return nullptr;
}

Application::Application()
{
    network::Manager m;
    m.setRemoteHost("192.168.137.1");
    //serverThread = m.runServiceThread();
    clientThread = m.runServiceThread();
    CommNet c(this);
//    server = m.createServer(std::make_shared<CommNet>(c), 50);
//    server->start();
    client = m.createClient(std::make_shared<CommNet>(c));
    client->start();

//    network::Message msg(1, "Hoi Jelle!");
//    client->getConnection()->writeMessage(msg);
}

void Application::joinServerThread() {
    serverThread->join();
}

void Application::joinClientThread(){
    clientThread->join();
}
