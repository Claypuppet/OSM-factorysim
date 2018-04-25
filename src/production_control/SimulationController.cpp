//
// Created by sven on 22-4-18.
//

#include "SimulationController.h"
#include "SimulationConnectionHandler.h"
#include "States/LoadConfigState.h"

Core::SimulationController::SimulationController() {
    serverThread = m.runServiceThread();
    Core::SimulationConnectionHandler handler;
    handler.addObserver(*this);
    server = m.createServer(std::make_shared<Core::SimulationConnectionHandler>(handler), 50);
    setCurrentState(std::make_shared<States::LoadConfigState>());
}

void Core::SimulationController::handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) {

}
