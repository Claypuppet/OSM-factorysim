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
  void registerMachine();

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
   * Function to set a predetermined starting state for machine control's simulation statemachine
   */
  void setStartState();

  /**
   * Executed on receiving the "kNotifyEventTypeMachineInfoReceived" event to progress machine control's simulation statemachine
   * @param notification The notification received, contains the machine's info
   */
  void onMachineInfoReceived(const patterns::NotifyObserver::NotifyEvent &notification);

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
};
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
