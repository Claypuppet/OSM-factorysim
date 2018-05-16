
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
#include "SimulationMachine.h"

namespace core {

class Application : public patterns::NotifyObserver::Observer, public patterns::statemachine::Context {
 public:

  Application() = default;
  ~Application();

  void setMachines(const std::vector<MachinePtr>& simulationMachines);

  /**
  * A function to get a machine by its ID
  * @param machineId : The ID of the machine you are looking for
  * @return The machine with the requested ID or a nullptr when the machine doesn't exist
  */
  MachinePtr getMachine(uint32_t machineId);

  /**
   * Getter for server
   * @return server
   */
  Network::ServerPtr getServer();

  /**
  *  A function that joins the serverThread with the main thread
  */
  void joinServerThread();

  /**
  * A function to check if the applications server is running
  * @return True when the server is running
  */
  bool isServerRunning();

  /**
   * Setup server connections for application
   */
  void setupNetwork();

  /**
  *  Start the server if it's not running
  */
  void startServer();
  
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
  void setStartState();

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
  void setExecutaionConfiguration(const models::Configuration &executaionConfiguration);

 private:
  models::Configuration executaionConfiguration;
  std::vector<MachinePtr> machines;

  Network::ServerPtr server;
  ThreadPtr serverThread;
  Network::Manager manager;
};

}

#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
