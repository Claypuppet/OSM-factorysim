//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H

#include "Application.h"
#include "SimulationMachine.h"

namespace simulator {
class SimulationApplication : public machinecore::Application {
 public:
  SimulationApplication(uint16_t aMachineId);
  virtual ~SimulationApplication() = default;

 private:
  SimulationMachine machine;
};
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H
