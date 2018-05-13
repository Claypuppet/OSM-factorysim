// Created by don on 20-4-18.

#ifndef PRODUCTION_LINE_CONTROL_APPLICATION_H
#define PRODUCTION_LINE_CONTROL_APPLICATION_H


#include <patterns/statemachine/Context.h>
#include <patterns/notifyobserver/Observer.hpp>
#include "Machine.h"
#include "network/Manager.h"

namespace core {

    class Application : public Patterns::NotifyObserver::Observer, public Patterns::Statemachine::Context{
    public:
        /**
        * Default Constructor
        * Constructs application, creates a connectionhandler and starts server thread / instance
        */
        Application();

        ~Application() = default;

        /**
        * A function to add a machine to the machines vector
        * @param aMachine : The machine to add
        */
        void addMachine(const Machine &aMachine);

        /**
        * A function to get a machine by its ID
        * @param machineId : The ID of the machine you are looking for
        * @return The machine with the requested ID or a nullptr when the machine doesn't exist
        */
        MachinePtr getMachine(uint16_t machineId);

        /**
         * Getter for server
         * @return server
         */
        Network::ServerPtr getServer();

        /**
        *  A function that joins the serverThread with the main thread
        */
        void joinServerThread();

        /**
        * A function to check if the applications server is running
        * @return True when the server is running
        */
        bool isServerRunning();

        /**
         * Setup server connections for application
         */
        void setupNetwork();


        /**
        *  Start the server if it's not running
        */
        void startServer();

        /**
         * Function that handles incoming notifications
         * @param notification : The notification to handle
         */
        void handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) override;

    private:
        std::vector<Machine> machines;
        Network::ServerPtr server;
        ThreadPtr serverThread;
        Network::Manager m;
    };

}

#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
