//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H

#include "Application.h"
#include "SimulationMachine.h"

namespace simulator {

enum NotifyEventType{
  kNotifyEventTypeMachineConfigReceived
};

class SimulationApplication : public machinecore::Application {
 public:
  SimulationApplication(uint16_t aMachineId);
  virtual ~SimulationApplication() = default;

  void setStartState() override;

  virtual void handleNotification(const patterns::notifyobserver::NotifyEvent &notification);
};

typedef std::shared_ptr<SimulationApplication> SimulationApplicationPtr;

} // simulator

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H
