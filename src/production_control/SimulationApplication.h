//
// Created by klei on 5/16/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H

#include "Application.h"
#include "SimulationMachine.h"

namespace simulation {

class SimulationApplication : public core::Application {
 public:
  SimulationApplication() = default;
  virtual ~SimulationApplication() = default;

  /**
   * Calls the core application. After that this method will call turn on sim machines.
   */
  void setupNetwork() override;
  /**
   * Send message to all connected simulation machines to turn on
   */
  void turnOnSimulationMachines();

  /**
   * Send message to all connected simulation machines to turn on
   */
  void turnOffSimulationMachines();

  /**
   *
   * @param aMachines
   */
  void setMachines(const std::vector<SimulationMachinePtr> &aMachines);

 private:
  std::vector<SimulationMachinePtr> machines;

};

}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H
