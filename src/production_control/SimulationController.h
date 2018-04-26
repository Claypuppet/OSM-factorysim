//
// Created by sven on 22-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H

#include <network/Server.h>
#include <patterns/notifyobserver/Observer.hpp>
#include "Controller.h"


namespace Core {
    class SimulationController : public Controller, public Patterns::NotifyObserver::Observer {
    public:

        /**
         * executes productioncontrol, because no configfile was given
        */
        SimulationController();

        virtual ~SimulationController() = default;

        /**
         * start simulation by reading config file
         * @param aConfigFile : path to YAML config file
        */
        SimulationController(const std::string &);

        /**
        * checks if Event has defined action in this controller and tries to execute this, fires StateEvent or/and changes state
        * ---Supported Events---
        * SimulationRegisterMachine -> executes handleRegisterMachine(notification);
        * @param &notification : NotifyEvent implementation
        */
        void handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) override;


        void addMachine(Core::Machine &m);

        /**
         * @param machineId : Id of given machine
         * @return machinePointer : Pointer of requested machine
         */
        Core::MachinePtr getMachine(uint16_t id);

        /**
        * @param m : Id of given machine
        * @param connection : Connectionpointer to connection.
        * @return  : Pointer of requested machine
        */
        void sendConfigureMachine(uint16_t m, Network::ConnectionPtr &connection);
        void turnOnSimulationMachines();

        void setupNetwork();

        /**
         * sets start state and start sure that it stays in execution loop while executing == trues production control
        */
        void execute();

        /**
         * parses config file and sets to local variable model,
         * After that it will push imported machines into vector of machines
         *
        */
        void setConfigFromFile(const std::string &);

    private:
        /**
         * sets start state and fires event to read config file
        */
        void setStartState();

        /**
         * registers machine to vector of machines.
         * @param machineId : Id of given machine
         * @return machinePointer : Pointer of requested machine
         */
        void handleRegisterMachine(const Patterns::NotifyObserver::NotifyEvent &notification);


        void sendTurnOnMachine(uint16_t m);

        void sendTurnOffMachine(uint16_t m);

        Network::Manager networkManager;
        ThreadPtr serverThread;
        Network::ServerPtr server;
        std::vector<Core::Machine> machines;
        std::string configFile;


    };
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
