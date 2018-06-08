//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H

#include "Application.h"
#include "SimulationMachine.h"

namespace simulator {

/**
 * SimulationApplication expands Application for simulation purposes
 */
class SimulationApplication : public machinecore::Application {
 public:
  explicit SimulationApplication(uint16_t aMachineId);
  virtual ~SimulationApplication() = default;

};

typedef std::shared_ptr<SimulationApplication> SimulationApplicationPtr;

} // simulator

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H
