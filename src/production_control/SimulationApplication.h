//
// Created by klei on 5/16/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H

#include "Application.h"
#include "SimulationMachine.h"

namespace simulation {

/**
 * This class makes sure that the simulation in the application is executed correctly. It is used by the simulation
 * controller, just as the application is used by the controller. The simulation application overrides some methods to
 * give it a new or differenct implementation, and also adds the options to turn the simulation machines on and off.
 */
class SimulationApplication : public core::Application {
 public:
  SimulationApplication();
  virtual ~SimulationApplication() = default;
  void setMachines(const std::vector<core::MachinePtr> &aMachines) override;
  /**
   * Calls the core application. After that this method will call turn on sim machines.
   */
  void setupNetwork() override;

  /**
   * Get simulation machine by id
   */
  SimulationMachinePtr getSimulationMachine(uint16_t machineId);

  /**
   * Get all machines as simulation machines
   * @return : simulation machine list
   */
  const std::vector<SimulationMachinePtr> &getSimulationMachines() const;

  /**
   * Send message to all connected simulation machines to turn on
   */
  void turnOnSimulationMachines();

  /**
   * Send message to all connected simulation machines to turn on
   */
  void turnOffSimulationMachines();

  /**
   * Schedule machine notification for current time
   * @return : returns true if events have been scheduled
   */
  bool scheduleMachineNotifications();

  /**
   * Log statistics of the current operation
   */
  void debugLogCurrentStats();

  /**
   * Keeps specific notifications separate in machine, for later scheduling
   * @param notification : notification that arrived
   */
  void handleNotification(const patterns::notifyobserver::NotifyEvent &notification) override;

  /**
   * Applies delayed notifications and executes the scheduler
   */
  void executeScheduler() override;

  /**
   * also turns off the simulation machines
   */
  void workDayOver() override;

  /**
   * will finialize day log and move on to next day
   */
  void checkTimeToStartAgain() override;

  bool checkAllMachinesDisconnected() override;

 private:
  bool canScheduleNotifications;
  std::vector<SimulationMachinePtr> simulationMachines;

};

typedef std::shared_ptr<SimulationApplication> SimulationApplicationPtr;

}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H
