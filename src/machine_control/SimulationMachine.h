//
// Created by hqnders on 09/05/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H

#include "Machine.h"

#include <random>
#include <utils/RandomHelper.h>

namespace simulator {

/**
 * Simulation machine to be controlled by application for simulations purposes
 * Expands on Machine with the machine model
 */
class SimulationMachine : public machinecore::Machine {
 public:
  SimulationMachine(const models::Machine &machine);
  SimulationMachine(const SimulationMachine &other);
  ~SimulationMachine() override = default;
  bool configure() override;
  void selfTest() override;
  void takeInProduct() override;
  void processProduct() override;
  void takeOutProduct() override;
  bool checkBroken() override;

  void setConfigureStartState() override;
  void setInOperationStartState() override;

  static void setCanBreak(bool canBreak);
  uint64_t getMomentOfLastItemProcessed() const;

 protected:

  utils::UnsignedUniformDistribution breakDistribution;
  utils::NormalDistribution repairDistribution;
  uint64_t magicNumber = 0;
  uint64_t timeSinceBrokenCheck;
  uint64_t checkCycle;

  uint64_t momentOfLastItemProcessed;

  static bool canBreak;
};

typedef std::shared_ptr<SimulationMachine> SimulationMachinePtr;
} // namespace simulator

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H
