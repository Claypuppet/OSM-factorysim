//
// Created by don on 20-4-18.
//

#include "AppConnectionHandler.h"

#include "network/Server.h"
#include "network/Client.h"

Core::Application::Application()
{

}

void Core::Application::addMachine(const Machine &aMachine) {
    machines.push_back(aMachine);
}

Core::MachinePtr Core::Application::getMachine(uint16_t machineId) {
    for(Machine& m : machines)
    {
        if(m.getId() == machineId)
        {
            return std::make_shared<Machine>(m);
        }
    }
    return nullptr;
}

void Core::Application::setupNetwork(){
	if(server && server->isRunning()){
		return;
	}

	AppConnectionHandler connectionHandler;
//	handleNotificationsFor(connectionHandler);

	serverThread = m.runServiceThread();
	server = m.createServer(std::make_shared<AppConnectionHandler>(connectionHandler), 50);
	server->start();
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

void Core::Application::handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) {

}
