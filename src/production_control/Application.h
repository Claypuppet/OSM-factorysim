
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

class Application : public patterns::notifyobserver::Observer, public patterns::statemachine::Context {
 public:

  Application() = default;

  /**
   * Destruct a Application object
   */
  virtual ~Application();

  /**
   * Set the machines used in this application
   * @param aMachines
   */
  virtual void setMachines(const std::vector<MachinePtr> &aMachines);

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
  void handleNotification(const patterns::notifyobserver::NotifyEvent &notification) override;

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
  void registerMachine(uint16_t machineId, network::ConnectionPtr connection);

  /**
   * Set the pointer to productionline
   * - Used in the set config
   * @param productionLine shared pointer to productionLine
   */
  void setProductionLine(const models::ProductionLinePtr &productionLine);

  /**
   * Executes the scheduler. Checks if a machine can process a product.
   */
  virtual void executeScheduler();

  /**
   * Prepare the scheduler. Sends out the initial cofigure to connected machines.
   */
  virtual void prepareScheduler();

  /**
   * Change configuration
   * @param configurationId : config id to set
   * @param initial : first time calling this, default false
   */
  void changeProductionLineProduct(uint16_t configurationId);

  /**
   * Sets the status of a machine
   * @param machineId : Id of the machine
   * @param status : The new status
   * @return
   */
  bool setMachineStatus(uint16_t machineId, core::Machine::MachineStatus status);

  virtual const std::vector<MachinePtr> &getMachines() const;

 protected:
  /**
   * Checks if we need to change production, if so, prepare change.
   */
  void tryChangeProduction();

  /**
   * Handle register notification
   * @param id : Machine id
   * @param connection : Connection to this machine
   */
  void onHandleRegisterNotification(uint16_t id, const network::ConnectionPtr &connection);

  /**
   * Handle OK notification
   * @param id : Machine id
   * @param status : New status of this machine
   */
  void onHandleOKNotification(uint16_t id, models::Machine::MachineStatus status);

  /**
   * Handle NOK notification
   * @param id : Machine id
   * @param errorCode : Some error code
   */
  void onHandleNOKNotification(uint16_t id, models::Machine::MachineErrorCode errorCode);

  /**
   * Handles a product taken notification
   * @param machineId : Id of the machine that took products
   */
  void handleProductTakenNotification(uint16_t machineId);

  /**
   * Handles a product added notification
   * @param machineId : Id of the machine that added products
   */
  void handleProductAddedNotification(uint16_t machineId);

  models::ProductionLinePtr productionLine;
  std::vector<MachinePtr> machines;

  uint16_t currentProductId;
  uint64_t momentStartingCurrentProduct;

  std::map<uint16_t, MachinePtr> lastMachineInLine;
  std::map<uint16_t, std::vector<MachinePtr>> firstMachinesInLine;

  network::ServerPtr server;
  ThreadPtr serverThread;
  network::Manager manager;
};

typedef std::shared_ptr<Application> ApplicationPtr;

}

#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
