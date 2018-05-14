//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_APPLICATION_H
#define PRODUCTION_LINE_CONTROL_APPLICATION_H

#include "patterns/statemachine/Context.h"
#include "patterns/notifyobserver/Observer.hpp"
#include "network/Manager.h"
#include "NetworkComponent.h"
#include "Machine.h"
#include "models/MachineConfiguration.h"

//TODO: Implement Observer
namespace machinecore {
class Application
    : public patterns::statemachine::Context,
      public patterns::NotifyObserver::Observer {
 public:
  void handleNotification(const patterns::NotifyObserver::NotifyEvent &notification) override;

  /**
   * Constructor
   * @param aMachineInfo : The value for machineInfo
   */
  explicit Application(uint16_t aMachineId);

  /**
   * The destructor
   */
  ~Application() override;

  const Machine &getMachine() const {
    return machine;
  }

  void setMachine(const Machine &machine) {
    Application::machine = machine;
  }

  uint16_t getId() const {
    return id;
  }

  void setId(uint16_t id) {
    Application::id = id;
  }

  const std::vector<models::MachineConfiguration> &getConfigurations() const {
    return configurations;
  }

  void setConfigurations(const std::vector<models::MachineConfiguration> &configurations) {
    Application::configurations = configurations;
  }

  /**
   * Sets the starting state for the application's statemachine context
   */
  void setStartState();

  /**
   * Stops the network manager and joins the client thread
   */
  void stop();

 private:
  Network::Manager manager;
  Network::ClientPtr client;
  ThreadPtr clientThread;

  Machine machine;

  // Id of the machine
  uint16_t id;

  // Vector of possible configurations
  std::vector<models::MachineConfiguration> configurations;
};
}

#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
