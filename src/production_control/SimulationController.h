
#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H

#include <network/Server.h>
#include <patterns/notifyobserver/Observer.hpp>
#include <models/Configuration.h>

#include "Controller.h"
#include "SimulationMachine.h"
#include "SimulationApplication.h"

namespace simulation {

/**
 * Simualtion controller is the class that controls the application. As for the simualtion part, it will implement
 * a state machine, and control the application in a way that the machine control can be simulated.
 * Inherits Controller: as subclass of controller
 * Inherits Observer (notifier/observer pattern): To subscribe to network component event
 * Inherits Context (state machine pattern): To define simualtion states (connect to  sim. production control, turn
 *  machine on/off.
 */
class SimulationController
	: public core::Controller, public patterns::notifyobserver::Observer, public patterns::statemachine::Context {
 public:

  SimulationController();
  SimulationController(const SimulationController &) = delete;

  /**
   * Destruct
   */
  virtual ~SimulationController();

  /**
  * checks if Event has defined action in this controller and tries to execute this, fires StateEvent or/and changes state
  * ---Supported Events---
  * SimulationRegisterMachine -> executes handleRegisterMachine(notification);
  * @param &notification : NotifyEvent implementation
  */
  void handleNotification(const patterns::notifyobserver::NotifyEvent &notification) override;

  /**
   * Get machine by id
   * @param machineId : Id of machine
   * @return machinePointer : Machine if found else nullptr
   */
  SimulationMachinePtr getSimulationMachine(uint16_t id);

  /**
   * Setup simulation network communications
   */
  void setupNetwork();

  /**
   * sets start state and start sure that it stays in execution loop while executing == trues production control
   */
  virtual void execute() override;

  /**
   * Stops all services and ends the execution.
   */
  virtual void stop() override;

  /**
   * parses config file and sets to local variable model,
   * After that it will push imported machines into vector of machine
   * @param filePath : location of config file
   */
  void setConfiguration(const std::string &filePath);

  /**
   * Saves connection in machines vector (if exists) and sends configuration to machine.
   * if there is not yet a connection it will count the machine as machineCount
   * if machineCount has same number as machinevector size it will fire the kEventTypeSimulationConfigLoaded event
   * @param machineId : Id of given machine
   * @param connection : Network connection to the machine (session)
   */
  void registerMachine(uint16_t machineId, network::ConnectionPtr connection);

  /**
   * Machine is ready for simulation
   * @param machineId
   */
  void machineReady(uint16_t machineId);

  /**
   * check if all machines are ready for simulation
   * @return : true if all machines are ready
   */
  bool allMachinesReady();


  /**
   * Set the simulation start time
   */
  void setSimulationEndTime();


  /**
   * Check if simulation is over
   * @return simulationIsOver bool
   */
  bool isSimulationOver() const;

 private:

  /**
   * sets start state and fires event to read config file
  */
  void setStartState();

  /**
   * Function that handles notifications for registering machines
   * @param notification : NotifyEvent from notifier
   */
  void handleRegisterMachine(const patterns::notifyobserver::NotifyEvent &notification);

  /**
   * Function that handles notifications for readying a machine
   * @param notification : NotifyEvent from notifier
   */
  void handleMachineReady(const patterns::notifyobserver::NotifyEvent &notification);

  /**
   * Network properties
   */
  network::Manager networkManager;
  ThreadPtr serverThread;
  network::ServerPtr server;

  uint64_t simulationEndTimeInMillis;

  /**
   * Config properties
   */
  std::string configPath;
  std::shared_ptr<models::Configuration> configuration;
};
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
