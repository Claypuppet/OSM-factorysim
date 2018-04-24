//
// Created by don on 20-4-18.
//

#include "AppConnectionHandler.h"
#include "Application.h"

#include "network/Server.h"
#include "network/Client.h"
#include "TestConnectionHandler.h"


Core::Application::Application()
{
	serverThread = m.runServiceThread();
	server = m.createServer(std::make_shared<AppConnectionHandler>(this), 50);
}

void Core::Application::addMachine(const Machine &aMachine) {
    machines.push_back(aMachine);
}

Core::MachinePtr Core::Application::getMachine(uint8_t machineId) {
    for(Machine& m : machines)
    {
        if(m.getId() == machineId)
        {
            return std::make_shared<Machine>(m);
        }
    }
    return nullptr;
}

void Core::Application::joinServerThread() {
    serverThread->join();
}

void Core::Application::startServer(){
	if(!isServerRunning()){
		server->start();
	}

}

bool Core::Application::isServerRunning() {
    return server->isRunning();
}

Network::ServerPtr Core::Application::getServer() {
    return Network::ServerPtr();
}