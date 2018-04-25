//
// Created by sven on 22-4-18.
//

#include <cereal/archives/portable_binary.hpp>
#include <network/Protocol.h>
#include "SimulationController.h"
#include "SimulationConnectionHandler.h"
#include "States/LoadConfigState.h"
#include "NotificationTypes.h"

Core::SimulationController::SimulationController() {
    serverThread = m.runServiceThread();
    Simulation::SimulationConnectionHandler handler;
    handler.addObserver(*this);
    server = m.createServer(std::make_shared<Simulation::SimulationConnectionHandler>(handler), 50);
    setCurrentState(std::make_shared<States::LoadConfigState>());
}

void Core::SimulationController::handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) {
    switch (notification.getEventId()) {
        case SimulationregisterMachine:
            handleRegisterMachine(notification);
            break;
        default:
            break;
    }

}

Core::MachinePtr Core::SimulationController::getMachine(uint16_t machineId) {
    for (Machine &m : machines) {
        if (m.getId() == machineId) {
            return std::make_shared<Machine>(m);
        }
    }
    return nullptr;
}


void Core::SimulationController::addMachine(Core::Machine &m) {

}

void Core::SimulationController::sendConfigureMachine(uint16_t m, Network::ConnectionPtr &connection) {
    Core::MachinePtr machine = Core::SimulationController::getMachine(m);
    if (machine) {
        machine->setConnection(connection);

        std::vector<Models::MachineConfiguration> config;
        config = machine->getConfigurations();

        std::string binaryStream;

        std::stringstream outputBinary((std::ios::out | std::ios::binary));
        cereal::PortableBinaryOutputArchive archive(outputBinary);
        archive(config);

        binaryStream = outputBinary.str();

        Network::Message msg(Network::Protocol::SimMessageType::kSimMessageTypeConfig, binaryStream);
        machine->sendMessage(msg);
    }
}





