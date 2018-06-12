
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
  bool checkAllMachinesRegistered();

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
   * @param preparingShutdown : true if preparing to shutdown, changes the functionality of the scheduler
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

  /**
   * Makes a machine take products from its input buffer
   * @param machineId : The machine
   */
  void takeProductsFromBuffer(uint16_t machineId);

  /**
   * Makes a machine add products to its output buffer
   * @param machineId : The machine
   */
  void addProductsToBuffer(uint16_t machineId);

  virtual const std::vector<MachinePtr> &getMachines() const;

  /**
   * Saves statistics of all machines for the current timestamp
   */
  void saveMachineStatistics();

  /**
   * Logs statistics of a simulation to a result file
   */
  void logFinalStatistics();

  /**
   * Called by the prepare shutdown state to stop all machines
   */
  virtual void prepareForShutdown();

  /**
   * Called by the shutdown state to let the application know the work day is over.
   */
  virtual void workDayOver();

  /**
   * Called by the shutdown state to let the application know that all machines are shutdown.
   */
  virtual void checkTimeToStartAgain();

  /**
   * Check if all machines are idle
   * @param completelyIdle : Checks not only if state is idle, but also if input / output buffer is empty. default false
   * @return : True if all connected machines are in the idle state
   */
  bool checkAllMachinesIdle(bool completelyIdle = false);

  /**
   * Check if all machines are disconnected. used by shutdown state
   * @return : True if all connected machines are disconnected
   */
  virtual bool checkAllMachinesDisconnected();

 protected:

  /**
   * Calculates final statistics of all machines
   */
  void calculateFinalStatistics();

  /**
   * Checks if we need to change production, if so, prepare change.
   */
  bool shouldChangeProduction();

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
  void onHandleProductTakenFromBufferNotification(uint16_t machineId);

  /**
   * Handles a product added notification
   * @param machineId : Id of the machine that added products
   */
  void onHandleProductAddedToBufferNotification(uint16_t machineId);
  
  /**
   * Calculates the MTBF for a simulation with the times broken
   * @param timesBroken 
   */
  uint16_t getMTBFforTimesBroken(uint16_t timesBroken);

  models::ProductionLinePtr productionLine;
  std::vector<MachinePtr> machines;

  uint16_t currentProductId{};
  uint64_t momentStartingCurrentProduct{};
  uint64_t startTimeStamp;

  std::map<uint16_t, uint16_t> productPorportions;
  std::map<uint16_t, MachinePtr> lastMachineInLine;
  std::map<uint16_t, std::vector<MachinePtr>> firstMachinesInLine;

  network::ServerPtr server;
  ThreadPtr serverThread;
  network::Manager manager;

  /**
   * Timestamp, statistics
   */
  std::map<uint64_t, std::vector<models::MachineStatisticsPtr>> machineStatistics;

  std::vector<models::MachineFinalStatistics> finalStatistics;
  void onHandleMachineDisconnected(uint16_t id);
};

typedef std::shared_ptr<Application> ApplicationPtr;

}

#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
