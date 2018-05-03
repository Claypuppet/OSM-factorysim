//
// Created by sven on 22-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H

#include <network/Server.h>
#include <patterns/notifyobserver/Observer.hpp>
#include <models/Configuration.h>
#include "Controller.h"
#include "SimulationMachine.h"


namespace Simulation {

    /**
     * Simualtion controller is the class that controls the application. As for the simualtion part, it will implement
     * a state machine, and control the application in a way that the machine control can be simulated.
     * Inherits Controller: as subclass of controller
     * Inherits Observer (notifier/observer pattern): To subscribe to network component event
     * Inherits Context (state machine pattern): To define simualtion states (connect to  sim. production control, turn
     *  machine on/off.
     */
    class SimulationController : public Core::Controller, public Patterns::NotifyObserver::Observer, public Patterns::Statemachine::Context{
    public:

        /**
         *
        */
        SimulationController() = default;

		/**
		 * !! Temporary constructor with config file. command line argument object will be used in future.
		 * @param configFile: path to config file
		 */
		SimulationController(const std::string &configFile);

		/**
		 * Destruct
		 */
		virtual ~SimulationController() = default;


        /**
        * checks if Event has defined action in this controller and tries to execute this, fires StateEvent or/and changes state
        * ---Supported Events---
        * SimulationRegisterMachine -> executes handleRegisterMachine(notification);
        * @param &notification : NotifyEvent implementation
        */
        void handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) override;

        /**
         * Get machine by id
         * @param machineId : Id of machine
         * @return machinePointer : Machine if found else nullptr
         */
		SimulationMachinePtr getMachine(uint16_t id);

        /**
         * Send message to all connected simulation machines to turn on
         */
        void turnOnSimulationMachines();

        /**
         * Send message to all connected simulation machines to turn on
         */
        void turnOffSimulationMachines();

        /**
         * Setup simulation network communications
         */
        void setupNetwork();

        /**
         * sets start state and start sure that it stays in execution loop while executing == trues production control
         */
        virtual void execute() override;

        /**
         * Stops all services and ends the execution.
         */
        virtual void stop() override;

        /**
         * parses config file and sets to local variable model,
         * After that it will push imported machines into vector of machine
         * @param filePath : location of config file
         */
        void setConfigFromFile(const std::string &filePath);

		/**
		 *
         * Saves connection in machines vector (if exists) and sends configuration to machine.
		 * @param machineId : Id of given machine
		 * @param connection : Network connection to the machine (session)
		 */
		void registerMachine(uint16_t machineId, Network::ConnectionPtr connection);

    private:

        /**
         * sets start state and fires event to read config file
        */
        void setStartState();

        void handleRegisterMachine(const Patterns::NotifyObserver::NotifyEvent &notification);

        /**
         * Network properties
         */
        Network::Manager networkManager;
        ThreadPtr serverThread;
        Network::ServerPtr server;

        /**
         * SimulationMachines
         */
        std::vector<SimulationMachinePtr> machines;

        /**
         * Config properties
         */
        std::string configPath;
		Models::Configuration configuration;


    };
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
