//
// Created by sven on 22-4-18.
//

#include "SimulationController.h"
#include "SimulationConnectionHandler.h"

Core::SimulationController::SimulationController() {
    serverThread = m.runServiceThread();
    Core::SimulationConnectionHandler handler;
    handler.addObserver(*this);
    server = m.createServer(std::make_shared<Core::SimulationConnectionHandler>(handler), 50);
}

Core::SimulationController::~SimulationController() {

}
