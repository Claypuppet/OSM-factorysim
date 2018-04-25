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

        void handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) override;

        virtual ~SimulationController() = default;

        void addMachine(Core::Machine& m);
        Core::MachinePtr getMachine(uint16_t id);

    private:
        Network::Manager m;
        ThreadPtr serverThread;
        Network::ServerPtr server;
        std::vector<Core::Machine> machines;

        void handleRegisterMachine(const Patterns::NotifyObserver::NotifyEvent &notification);
    };
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
