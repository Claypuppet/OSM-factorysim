//
// Created by klei on 6/5/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONMACHINEPOSTPROCESS_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONMACHINEPOSTPROCESS_H

#include "SimulationMachine.h"

namespace simulator {

/**
 * A simulation machine with post processing (like drying a table after painting it)
 */
class SimulationMachinePostProcess : public SimulationMachine {
 public:
  SimulationMachinePostProcess(const models::Machine &machine);
  ~SimulationMachinePostProcess() override = default;
  void processProduct() override;
  void takeOutProduct() override;
  bool configure() override;


 private:
  void performPostProcess();

  // moment of the last item that started the post process-process.
  uint64_t momentOfLastItemStartedInPostProcess;
};

}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONMACHINEPOSTPROCESS_H
