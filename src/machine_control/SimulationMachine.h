//
// Created by hqnders on 09/05/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H

#include "Machine.h"

#include <random>

namespace simulator {

/**
 * Simulation machine to be controlled by application for simulations purposes
 * Expands on Machine with the machine model
 */
class SimulationMachine : public machinecore::Machine {
 public:
  SimulationMachine();
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
  static void setTimeCycles(bool timeCycles);

 private:
  std::default_random_engine generator;
  std::uniform_int_distribution<uint64_t> distribution;
  uint8_t magicNumber = 0;
  uint64_t timeSinceBrokenCheck;
  uint64_t checkCycle;

  static bool canBreak;
  static bool timeCycles;
};

typedef std::shared_ptr<SimulationMachine> SimulationMachinePtr;
} // namespace simulator

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H
