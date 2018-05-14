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

  void handleNotification(const patterns::NotifyObserver::NotifyEvent &notification) override;

  /**
   * Sets the ip address of the production control
   * @param setRemoteHost : The new ip-address of the host
   */
  void setRemoteHost(const std::string &setRemoteHost);
  void setupNetwork();

 private:
  void setStartState();

  void onMachineInfoReceived(const patterns::NotifyObserver::NotifyEvent &notification);

  bool executing;

  ThreadPtr clientThread;
  Network::Manager networkManager;
  Network::ClientPtr client;
  SimulationApplication application;
};
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
