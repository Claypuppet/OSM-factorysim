//
// Created by sven on 22-4-18.
//

#include <cereal/archives/portable_binary.hpp>
#include <network/Protocol.h>
#include <command_line/CommandLineArguments.h>
#include <models/Configuration.h>
#include "SimulationController.h"
#include "SimulationConnectionHandler.h"
#include "states_controller/LoadConfigState.h"
#include "NotificationTypes.h"
#include "ConfigurationReader.h"

Core::SimulationController::SimulationController() : executing(false){
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
//TODO Add simulated machine to list of simulated machines ???
}


void Core::SimulationController::setupNetwork(){
    serverThread = networkManager.runServiceThread();

    Simulation::SimulationConnectionHandler connectionHandler;
    handleNotificationsFor(connectionHandler);

    server = networkManager.createServer(std::make_shared<Simulation::SimulationConnectionHandler>(connectionHandler), 50);
    server->start();
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


void Core::SimulationController::handleRegisterMachine(const Patterns::NotifyObserver::NotifyEvent &notification) {

    auto id = notification.getArgumentAsType<uint16_t>(0);
    auto connection = notification.getArgumentAsType<Network::ConnectionPtr>(1);
    registerMachine(id, connection);
}


void Core::SimulationController::registerMachine(uint16_t machineId, Network::ConnectionPtr connection) {

    sendConfigureMachine(machineId, connection);
}


void Core::SimulationController::execute() {
    setStartState();

    executing = true;
    while(executing){
        run();
    }
}

void Core::SimulationController::setStartState() {
    auto startState = std::make_shared<States::LoadConfigState>(*this);
    setCurrentState(startState);

    // TEMP!!!! set first file
	auto e = std::make_shared<States::Event>(States::kEventTypeReadConfigFile);
	e->setArgument<std::string>(configFile);
	scheduleEvent(e);
}

Core::SimulationController::SimulationController(const std::string &aConfigFile) : configFile(aConfigFile) {

}

void Core::SimulationController::setConfigFromFile(const std::string &configFile) {

	ConfigLoader::ConfigurationReader reader;
	Models::Configuration model;
	reader.readConfigurationFile(configFile, model);

	Models::ProductionLine productionline = model.getProductionLineConfiguration();
	Models::SimulationInfo simInfo = model.getSimulationInfoConfiguration();

	std::vector<Models::Machine> machines = productionline.getMachines();
	for(Models::Machine m : machines)
	{
		machines.push_back(m);
	}

	// If simulation, add sim state
//	if(){
	auto e = std::make_shared<States::Event>(States::kEventTypeSimulationConfigLoaded);
	scheduleEvent(e);
//	}
//	else{
//		auto e = std::make_shared<States::Event>(States::kEventTypeProductionConfigLoaded);
//		scheduleEvent(e);
//	}

}

