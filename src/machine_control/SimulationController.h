#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H

// standard libraries
// ...

// libraries
#include <network/Manager.h>
#include <network/Client.h>
#include <patterns/notifyobserver/Observer.hpp>

// other
#include "SimulationNetworkComponent.h"
#include "Controller.h"
#include "SimulationApplication.h"
#include "SimulationMachine.h"

namespace simulator {

class SimulationController
	: public machinecore::Controller,
	  public patterns::statemachine::Context,
	  public patterns::notifyobserver::Observer {

 public:
  SimulationController(uint16_t aMachineId);
  ~SimulationController() override;

  /**
   * Starts the controller and puts it in a run cycle
   */
  void execute() override;

  /**
   * Stops the networkManager and execution of the controller
   */
  void stop();

  /**
   * Called to set simulation configurations of it's application to the parameter's configurations
   * @param machine : The received simulation configurations
   */
  void setMachineInfo(const models::MachinePtr &machine);

  /**
   * Called when notfified, takes the notification and handles it accoardingly
   * @param notification The received notification
   */
  void handleNotification(const patterns::notifyobserver::NotifyEvent &notification) override;

  /**
   * Sets the ip address of the production control
   * @param setRemoteHost : The new ip-address of the host
   */
  void setRemoteHost(const std::string &setRemoteHost);

  /**
   * Initialises the clientThread, networkManager and client
   */
  void setupNetwork();

  /**
   * Sends a message to Production Control to receive simulation configurations
   */
  void registerMachine();

  /**
   * Sends a message to Production Control that the machine is ready for simulation
   */
  void machineReady();

 private:
  /**
   * Function to set a predetermined starting state for machine control's simulation statemachine
   */
  void setStartState();

  /**
   * Executed on receiving the "kNotifyEventTypeMachineInfoReceived" event to progress machine control's simulation statemachine
   * @param notification The notification received, contains the machine's info
   */
  void onSimulationConfigurationsReceived(const patterns::notifyobserver::NotifyEvent &notification);

  /**
   * Executed on receiving the "kNotifyEventTypeServiceStarted" event to progress machine control's simulation statemachine
   */
  void onServiceStarted();

  /**
   * Executed on receiving the "kNotifyEventTypeServiceError" event to progress machine control's simulation statemachine
   */
  void onServiceError();

  /**
   * Executed on receiving the "kNotifyEventTurnOnReceived" event to progress machine control's simulation statemachine
   */
  void onTurnOnReceived();

  /**
   * Executed on receiving the "kNotifyEventTurnOffReceived" event to progress machine control's simulation statemachine
   */
  void onTurnOffReceived();

  // The thread which the client runs on
  ThreadPtr clientThread;

  // The network's manager to manage the connection to Production Control
  network::Manager networkManager;

  // The network's client
  network::ClientPtr client;

  SimulationCommunication::SimulationNetworkComponentPtr simulationNetworkComponent;
};
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
