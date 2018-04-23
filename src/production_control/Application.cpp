//
// Created by don on 20-4-18.
//

#include "AppConnectionHandler.h"
#include "Application.h"

#include "network/Server.h"
#include "network/Client.h"
#include "TestConnectionHandler.h"



/**
 * Default Constructor
 * Constructs application, creates a connectionhandler and starts server thread / instance
 */
Application::Application()
		: connectionHandler(std::make_shared<AppConnectionHandler>(this))
{
	serverThread = m.runServiceThread();
	server = m.createServer(connectionHandler, 50);
}

/**
 * A function to add a machine to the machines vector
 * @param aMachine the machine to add
 */

void Application::addMachine(const Machine &aMachine) {
    machines.push_back(aMachine);
}

/**
 * A function to get a machine by its ID
 * @param machineId The ID of the machine you are looking for
 * @return The machine with the requested ID or a nullptr when the machine doesn't exist
 */
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

/**
 *  A function that joins the serverThread with the main thread
 */
void Application::joinServerThread() {
    serverThread->join();
}


/**
 *  Start the server if it's not running
 */
void Application::startServer(){
	if(!isServerRunning()){
		server->start();
	}

}

/**
 * A function to check if the applications server is running
 * @return True when the server is running
 */

bool Application::isServerRunning() {
    return server->isRunning();
}
