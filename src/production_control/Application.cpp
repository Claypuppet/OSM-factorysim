//
// Created by don on 20-4-18.
//

#include "Application.h"

#include "AppConnectionHandler.h"
#include "network/Server.h"
#include "network/Client.h"

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
 * Default Constructor
 * Constructs application and starts a server
 */
Application::Application()
{
    Network::Manager m;
    m.setRemoteHost("192.168.137.1");
    serverThread = m.runServiceThread();
    AppConnectionHandler c(this);
    server = m.createServer(std::make_shared<AppConnectionHandler>(c), 50);
    server->start();
}

/**
 *  A function that joins the serverThread with the main thread
 */
void Application::joinServerThread() {
    serverThread->join();
}

/**
 * A function to check if the applications server is running
 * @return True when the server is running
 */

bool Application::isServerRunning() {
    return server->isRunning();
}
