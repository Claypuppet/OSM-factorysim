//
// Created by don on 20-4-18.
//

#include "AppConnectionHandler.h"

#include "network/Server.h"
#include "network/Client.h"

core::Application::Application()
{

}

void core::Application::addMachine(const Machine &aMachine) {
    machines.push_back(aMachine);
}

core::MachinePtr core::Application::getMachine(uint16_t machineId) {
    for(Machine& m : machines)
    {
        if(m.getId() == machineId)
        {
            return std::make_shared<Machine>(m);
        }
    }
    return nullptr;
}

void core::Application::setupNetwork(){
	if(server && server->isRunning()){
		return;
	}

	AppConnectionHandler connectionHandler;
//	handleNotificationsFor(connectionHandler);

	serverThread = m.runServiceThread();
	server = m.createServer(std::make_shared<AppConnectionHandler>(connectionHandler), 50);
	server->start();
}

void core::Application::joinServerThread() {
    serverThread->join();
}

void core::Application::startServer(){
	if(!isServerRunning()){
		server->start();
	}

}

bool core::Application::isServerRunning() {
    return server->isRunning();
}

Network::ServerPtr core::Application::getServer() {
    return Network::ServerPtr();
}

void core::Application::handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) {

}
