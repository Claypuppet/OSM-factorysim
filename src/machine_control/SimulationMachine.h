//
// Created by hqnders on 09/05/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H

#include "Machine.h"

namespace simulator {

/**
 * Simulation machine to be controlled by application for simulations purposes
 * Expands on Machine with the machine model
 */
class SimulationMachine : public machinecore::Machine {
 public:
  SimulationMachine() = default;
  ~SimulationMachine() override = default;
  bool configure() override;
  void selfTest() override;
  void takeInProduct() override;
  void processProduct() override;
  void takeOutProduct() override;

  void setConfigureStartState() override;
  void setInOperationStartState() override;
};

typedef std::shared_ptr<SimulationMachine> SimulationMachinePtr;
} // namespace simulator

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H
