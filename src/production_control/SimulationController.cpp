//
// Created by sven on 22-4-18.
//

#include <cstdint>

#include <cereal/archives/portable_binary.hpp>
#include <network/Protocol.h>
#include <utils/CommandLineArguments.h>
#include <models/Configuration.h>

#include "SimulationController.h"
#include "SimulationConnectionHandler.h"
#include "states_controller/LoadConfigState.h"
#include "NotificationTypes.h"
#include "configuration_reader/ConfigurationReader.h"

namespace simulation {

SimulationController::SimulationController() : core::Controller() {
  application = std::make_shared<SimulationApplication>();
}

SimulationController::~SimulationController() {

  networkManager.stop();
  if (serverThread && serverThread->joinable()) {
	serverThread->join();
  }
}

void SimulationController::handleNotification(const patterns::notifyobserver::NotifyEvent &notification) {
  switch (notification.getEventId()) {
	case NotifyEventIds::SimulationNotificationTypes::eSimRegisterMachine: {
	  handleRegisterMachine(notification);
	  break;
	}

	case NotifyEventIds::eSimMachineReady: {
	  handleMachineReady(notification);
	  break;
	}

	default: {
	  std::cerr << "unhandled notification with id " << notification.getEventId() << std::endl;
	}
	  break;
  }

}

SimulationMachinePtr SimulationController::getSimulationMachine(uint16_t machineId) {
  auto machineItr = std::find_if(
	  machines.begin(),
	  machines.end(),
	  [machineId](const core::MachinePtr &m1) { return m1->getId() == machineId; }
  );
  if (machineItr != machines.end()) {
	return std::dynamic_pointer_cast<SimulationMachine>(*machineItr);
  }
  return nullptr;
}

void SimulationController::setupNetwork() {
  if (server && server->isRunning()) {
	return;
  }

  simulationcommunication::SimulationConnectionHandler connectionHandler;
  handleNotificationsFor(connectionHandler);

  networkManager.setLocalPort(network::Protocol::PORT_SIMULATION_COMMUNICATION);
  serverThread = networkManager.runServiceThread();
  server = networkManager.createServer(std::make_shared<simulationcommunication::SimulationConnectionHandler>(connectionHandler), 50);
  server->start();
}

void SimulationController::handleRegisterMachine(const patterns::notifyobserver::NotifyEvent &notification) {
  auto id = notification.getArgumentAsType<uint16_t>(0);
  auto connection = notification.getArgumentAsType<network::ConnectionPtr>(1);

  auto event = std::make_shared<states::Event>(states::kEventTypeMachineConnected);
  event->addArgument(id);
  event->addArgument(connection);
  scheduleEvent(event);
}

void SimulationController::handleMachineReady(const patterns::notifyobserver::NotifyEvent &notification) {
  auto id = notification.getArgumentAsType<uint16_t>(0);

  auto event = std::make_shared<states::Event>(states::kEventTypeMachineReady);
  event->addArgument(id);
  scheduleEvent(event);
}

void SimulationController::execute() {
  if (executing) {
	return;
  }
  executing = true;
  setStartState();
  while (executing) {
	// Main
	run();
  }
}

void SimulationController::stop() {
  Controller::stop();
  networkManager.stop();
  if (serverThread && serverThread->joinable()) {
	serverThread->join();
  }
}

void SimulationController::setStartState() {
  auto startState = std::make_shared<states::LoadConfigState>(*this);
  setCurrentState(startState);

  // TEMP!!!!? set first config file as event for LoadConfigState
  configPath = utils::CommandLineArguments::i().getArg(0);
  if (configPath.empty()) {
	// throw exception when no argument is given.
	throw std::runtime_error("No configuration file argument found!");
  }
  auto event = std::make_shared<states::Event>(states::kEventTypeReadConfigFile);
  event->setArgument<std::string>(configPath);
  scheduleEvent(event);
}

void SimulationController::setConfigFromFile(const std::string &filePath) {

  ConfigLoader::ConfigurationReader reader;

  reader.readConfigurationFile(filePath, configuration);
  auto simInfo = configuration.getSimulationInfoConfiguration();

  auto productionline = configuration.getProductionLineConfiguration();
  auto machineInfos = productionline.getMachines();

  for (const models::Machine &m : machineInfos) {
	SimulationMachine machine(m);
	machines.emplace_back(std::make_shared<SimulationMachine>(machine));
  }

  application->setProductionLine(configuration.getProductionLineConfiguration());
  application->setMachines(machines);


  // If simulation, add sim state event
  if (true) { //TODO: For now always true till we support non-simulations
	auto event = std::make_shared<states::Event>(states::kEventTypeSimulationConfigLoaded);
	scheduleEvent(event);
  } else {
	auto e = std::make_shared<states::Event>(states::kEventTypeProductionConfigLoaded);
	scheduleEvent(e);
  }

}

void SimulationController::registerMachine(uint16_t machineId, network::ConnectionPtr connection) {
  auto machine = getSimulationMachine(machineId);
  if (machine) {
	machine->setSimulationConnection(connection);
	machine->sendSimulationConfiguration();
  }
}

bool SimulationController::allMachinesReady() {
  for (const auto &machine : machines) {
	auto simMachine = std::dynamic_pointer_cast<SimulationMachine>(machine);
	if (!simMachine || !simMachine->isReadyForSimulation()) {
	  return false;
	}
  }
  return true;
}

void SimulationController::machineReady(uint16_t machineId) {
  auto machine = getSimulationMachine(machineId);
  if (machine) {
	machine->setReady(true);

	// Add new event if all machines are now connected
	if (allMachinesReady()) {
	  auto event = std::make_shared<states::Event>(states::kEventTypeAllMachinesReadyForSimulation);
	  scheduleEvent(event);
	}
  }
}
} // simulation

