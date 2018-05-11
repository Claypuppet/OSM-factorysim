//
// Created by sven on 22-4-18.
//

#include <cereal/archives/portable_binary.hpp>
#include <network/Protocol.h>
#include <utils/CommandLineArguments.h>
#include <models/Configuration.h>

#include "SimulationController.h"
#include "SimulationConnectionHandler.h"
#include "states_controller/LoadConfigState.h"
#include "NotificationTypes.h"
#include "ConfigurationReader.h"


namespace simulation {

	void SimulationController::handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) {
		switch (notification.getEventId()) {
			case NotifyEventIds::eControllerRegisterMachine:
				handleRegisterMachine(notification);
				break;
			case NotifyEventIds::eControllerMachineReady:
				handleMachineReady(notification);
				break;
			default:
				std::cerr << "unhandled notification with id " << notification.getEventId() << std::endl;
				break;
		}

	}

	SimulationMachinePtr SimulationController::getMachine(uint16_t machineId) {
		auto machineItr = std::find_if(
				machines.begin(),
				machines.end(),
				[machineId](const SimulationMachinePtr &m1){ return m1->getId() == machineId;}
		);
		return machineItr != machines.end() ? *machineItr : nullptr;
	}

	void SimulationController::setupNetwork(){
		if(server && server->isRunning()){
			return;
		}

		SimulationConnectionHandler connectionHandler;
		handleNotificationsFor(connectionHandler);

		networkManager.setLocalPort(Network::Protocol::kPortSimulationCommunication);
		serverThread = networkManager.runServiceThread();
		server = networkManager.createServer(std::make_shared<SimulationConnectionHandler>(connectionHandler), 50);
		server->start();
	}

	void SimulationController::handleRegisterMachine(const Patterns::NotifyObserver::NotifyEvent &notification) {
		auto id = notification.getArgumentAsType<uint16_t>(0);
		auto connection = notification.getArgumentAsType<Network::ConnectionPtr>(1);

		auto event = std::make_shared<States::Event>(States::kEventTypeMachineConnected);
		event->addArgument(id);
		event->addArgument(connection);
		scheduleEvent(event);
	}

	void SimulationController::handleMachineReady(const Patterns::NotifyObserver::NotifyEvent &notification) {
		auto id = notification.getArgumentAsType<uint16_t>(0);

		auto event = std::make_shared<States::Event>(States::kEventTypeMachineReady);
		event->addArgument(id);
		scheduleEvent(event);
	}

	void SimulationController::execute() {
		if(executing){
			return;
		}
		executing = true;
		setStartState();
		while (executing){
			// Main
			run();
		}
	}

	void SimulationController::stop() {
		Controller::stop();
		networkManager.stop();
		serverThread->join();
	}

	void SimulationController::setStartState() {
		auto startState = std::make_shared<States::LoadConfigState>(*this);
		setCurrentState(startState);

		// TEMP!!!!? set first config file as event for LoadConfigState
		configPath = utils::CommandLineArguments::i().getArg(0);
		if (configPath.empty()){
			// throw exception when no argument is given.
			throw std::runtime_error("No configuration file argument found!");
		}
		auto e = std::make_shared<States::Event>(States::kEventTypeReadConfigFile);
		e->setArgument<std::string>(configPath);
		scheduleEvent(e);
	}

	void SimulationController::setConfigFromFile(const std::string &filePath) {

		ConfigLoader::ConfigurationReader reader;

		reader.readConfigurationFile(filePath, configuration);
		auto simInfo = configuration.getSimulationInfoConfiguration();

		auto productionline = configuration.getProductionLineConfiguration();
		auto machineInfos = productionline.getMachines();

		for (const models::Machine &m : machineInfos)
		{
			SimulationMachine machine(m);
			machines.emplace_back(std::make_shared<SimulationMachine>(machine));
		}

		// If simulation, add sim state event
		if (true){ // For now always true till we support non-simulations
		auto e = std::make_shared<States::Event>(States::kEventTypeSimulationConfigLoaded);
		scheduleEvent(e);
		}
		else{
			auto e = std::make_shared<States::Event>(States::kEventTypeProductionConfigLoaded);
			scheduleEvent(e);
		}

	}

	void SimulationController::turnOnSimulationMachines() {
		// TODO: send turn on message to connected sim machines
	}

	void SimulationController::turnOffSimulationMachines() {
		// TODO: send turn off message to connected sim machines
	}


	void SimulationController::registerMachine(uint16_t machineId, Network::ConnectionPtr connection) {
		auto m = getMachine(machineId);
		if(m){
			m->setSimulationConnection(connection);
			m->sendSimulationConfiguration();
		}
	}

	bool SimulationController::allMachinesReady() {
	  	for (const auto &machine : machines){
	    	if (!machine->isReadyForSimulation()){
	      		return false;
	    	}
	  	}
	  	return true;
	}

	void SimulationController::machineReady(uint16_t machineId) {
		auto machine = getMachine(machineId);
		if(machine){
		  machine->setReady(true);

			// Add new event if all machines are now connected
			if (allMachinesReady()) {
				auto e = std::make_shared<States::Event>(States::kEventTypeAllMachinesReadyForSimulation);
				scheduleEvent(e);
			}
		}
	}
}

