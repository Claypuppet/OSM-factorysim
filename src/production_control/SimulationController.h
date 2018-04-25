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

    private:
        Network::Manager m;
        ThreadPtr serverThread;
        Network::ServerPtr server;
    };
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
