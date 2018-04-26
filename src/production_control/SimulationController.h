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
        SimulationController();

        virtual ~SimulationController() = default;

        SimulationController(const std::string &);

/**
     * checks if Event has defined action in this controller and tries to execute this, fires StateEvent or/and changes state
     * Supported Events
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

        void sendConfigureMachine(uint16_t m, Network::ConnectionPtr &connection);
        void turnOnSimulationMachines();

        void setupNetwork();

        void execute();


        void setConfigFromFile(const std::string &);

    private:
        void setStartState();

        /**
         * registers machine
 * @param machineId : Id of given machine
 * @return machinePointer : Pointer of requested machine
 */
        void handleRegisterMachine(const Patterns::NotifyObserver::NotifyEvent &notification);

        void registerMachine(uint16_t machineId, const Network::ConnectionPtr connection);

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
