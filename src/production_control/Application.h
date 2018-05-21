
#ifndef PRODUCTION_LINE_CONTROL_APPLICATION_H
#define PRODUCTION_LINE_CONTROL_APPLICATION_H

// standard libary includes
#include <vector>
#include <cstdint>

// other library includes
#include <patterns/statemachine/Context.h>
#include <patterns/notifyobserver/Observer.hpp>
#include <models/Configuration.h>

// project file includes
#include "Machine.h"
#include "network/Manager.h"

namespace core {

class Application : public patterns::NotifyObserver::Observer, public patterns::statemachine::Context {
 public:

  Application() = default;
  virtual ~Application();

  virtual /**
   * Set the machines used in this application
   * @param aMachines
   */
  void setMachines(const std::vector<MachinePtr>& aMachines);

  /**
  * A function to get a machine by its ID
  * @param machineId : The ID of the machine you are looking for
  * @return The machine with the requested ID or a nullptr when the machine doesn't exist
  */
  MachinePtr getMachine(uint16_t machineId);

  /**
   * Setup server connections for application
   */
  virtual void setupNetwork();

  /**
   * Stops the server if it's running
   */
  void stopServer();

  /**
   * Function that handles incoming notifications
   * @param notification : The notification to handle
   */
  void handleNotification(const patterns::NotifyObserver::NotifyEvent &notification) override;

  /**
   * Set the start state
   */
  virtual void setStartState();

  /**
   * Check if all machines are ready
   */
  bool allMachinesRegistered();

  /**
   * set the connection of a machine by a specific machineId
   * @param machineId the id of the machine
   * @param connection the connection of the machine
   */
  void registerMachine(uint16_t machineId, Network::ConnectionPtr connection);

  /**
   * Set the coniguration used by the execution of this application
   * @param executaionConfiguration
   */
  void setProductionLine(const models::ProductionLine &executaionConfiguration);

  /**
   * Executes the scheduler. Checks if a machine can process a product.
   */
  virtual void executeScheduler();

  /**
   * Prepare the scheduler. Sends out the initial cofigure to connected machines.
   */
  virtual void prepareScheduler();

  /**
   *
   * Change configuration
   * @param configurationId : config id to set
   */
  virtual void changeProductionLineProduct(uint16_t configurationId);

  /**
   * Sets the status of a machine
   * @param machineId : Id of the machine
   * @param status : The new status
   * @return
   */
  bool setMachineStatus(uint16_t machineId, core::Machine::MachineStatus status);

  const std::vector<MachinePtr> &getMachines() const;

 protected:
  models::ProductionLine productionLine;
  std::vector<MachinePtr> machines;
  uint16_t currentProduct;

  Network::ServerPtr server;
  ThreadPtr serverThread;
  Network::Manager manager;
};

typedef std::shared_ptr<Application> ApplicationPtr;

}

#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
