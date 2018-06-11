
#include <cstdint>

#include <configuration_serializer/ConfigurationReader.h>
#include <network/Protocol.h>
#include <utils/CommandLineArguments.h>
#include <models/Configuration.h>
#include <utils/time/Time.h>
#include <utils/TimeHelper.h>

#include "SimulationController.h"
#include "SimulationConnectionHandler.h"
#include "states_controller/LoadConfigState.h"
#include "NotificationTypes.h"
#include "ResultLogger.h"

namespace simulation {

// monday jan 1st 2018 00:00:00:000
const uint64_t ABSOLUTE_START_TIME = 1514764800000;

SimulationController::SimulationController() : core::Controller(), simulationEndTimeInMillis(0) {
  application = std::make_shared<SimulationApplication>();
  // Use custom time
  auto &time = utils::Time::getInstance();
  time.setType(utils::customTime);
  time.syncTime(ABSOLUTE_START_TIME);
}

SimulationController::~SimulationController() {
  stop();
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
      break;
    }
  }

}

bool SimulationController::simulationIsOver() const {
  return utils::TimeHelper::getInstance().getCurrentWeek() == configuration->getSimulationInfo()->getDurationInWeeks();
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
  server = networkManager.createServer(std::make_shared<simulationcommunication::SimulationConnectionHandler>(
      connectionHandler), 50);
  server->start();
}

void SimulationController::handleRegisterMachine(const patterns::notifyobserver::NotifyEvent &notification) {
  auto id = notification.getArgumentAsType<uint16_t>(0);
  auto connection = notification.getArgumentAsType<network::ConnectionPtr>(1);

  auto event = std::make_shared<states::Event>(states::kEventTypeMachineRegistered);
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

void SimulationController::setConfiguration(const std::string &filePath) {
  auto configurationReader = configurationserializer::ConfigurationReader::getInstance();

  configuration = configurationReader.deserialize(filePath);

  auto simulationInfo = configuration->getSimulationInfo();

  utils::TimeHelper::getInstance().initialize(simulationInfo->getStartHourOfWorkDay(),
                                              simulationInfo->getWorkDayDurationInHours());

  const auto &productionLineModel = configuration->getProductionLine();
  application->setProductionLine(productionLineModel);

  const auto &machineModels = productionLineModel->getMachines();

  for (const auto &machineModel : machineModels) {
    machines.emplace_back(std::make_shared<SimulationMachine>(*machineModel));
  }

  application->setMachines(machines);

  // If simulation, add sim state event
  if (true) { //TODO: For now always true till we support non-simulations
    auto event = std::make_shared<states::Event>(states::kEventTypeSimulationConfigLoaded);
    scheduleEvent(event);
  } else {
    auto e = std::make_shared<states::Event>(states::kEventTypeProductionConfigLoaded);
    scheduleEvent(e);
  }

  core::ResultLogger::getInstance().initializeLog(filePath, configuration->getName());
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

