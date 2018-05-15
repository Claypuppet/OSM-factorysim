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
      public patterns::NotifyObserver::Observer {

 public:
  SimulationController(uint16_t aMachineId);
  ~SimulationController() override;

  void execute();
  void stop();
  
  /**
   * Called to set simulation configurations of it's application to the parameter's configurations
   * @param simulationConfigurations The received simulation configurations
   */
  void setSimulationConfigurations(std::vector<models::MachineConfiguration> simulationConfigurations);

  void handleNotification(const patterns::NotifyObserver::NotifyEvent &notification) override;

  /**
   * Sets the ip address of the production control
   * @param setRemoteHost : The new ip-address of the host
   */
  void setRemoteHost(const std::string &setRemoteHost);

  /**
   * Initialises the clientThread, networkManager and client
   */
  void setupNetwork();

 private:
  /**
   * Function to set a predetermined starting state for the statemachine
   */
  void setStartState();

  /**
   * Executed on receiving the "kNotifyEventTypeMachineInfoReceived" event to progress the statemachine
   * @param notification The notification received, contains the machine's info
   */
  void onSimulationConfigurationsReceived(const patterns::NotifyObserver::NotifyEvent &notification);

  /**
   * Executed on receiving the "kNotifyEventTypeServiceStarted" event to progress the statemachine
   */
  void onServiceStarted();

  /**
   * Executed on receiving the "kNotifyEventTypeServiceError" event to progress the statemachine
   */
  void onServiceError();

  /**
   * Sends a message to Production Control to receive simulation configurations
   */
  void registerMachine();

  // True or false depending on whether SimulationController is active
  bool executing;

  // The thread which the client runs on
  ThreadPtr clientThread;

  // The network's manager to manage the connection to Production Control
  Network::Manager networkManager;

  // The network's client
  Network::ClientPtr client;

  // The application which is controlled by the controller
  SimulationApplication application;

  SimulationCommunication::SimulationNetworkComponent simulationNetworkComponent;
};
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
