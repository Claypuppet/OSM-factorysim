
#ifndef PRODUCTION_LINE_CONTROL_CONTROLLERSTATE_H
#define PRODUCTION_LINE_CONTROL_CONTROLLERSTATE_H

#include "../SimulationController.h"

namespace states {

enum EventType {
  kEventTypeReadConfigFile,
  kEventTypeSimulationConfigLoaded,
  kEventTypeLocalSimulationConfigLoaded,
  kEventTypeProductionConfigLoaded,
  kEventTypeBroadcastSend,
  kEventTypeServerSetupFailed,
  kEventTypeMachineRegistered,
  kEventTypeAllMachinesReadyForSimulation,
  kEventTypeMachineReady,
  kEventTypeSimulationFinished
};

typedef patterns::statemachine::Event Event;
typedef patterns::statemachine::EventPtr EventPtr;

class ControllerState : public patterns::statemachine::State {

 public:
  virtual ~ControllerState() = default;
  virtual bool handleEvent(const EventPtr &event) override;
  virtual void entryAction() = 0;
  virtual void doActivity() = 0;
  virtual void exitAction() = 0;

 protected:
  ControllerState(simulation::SimulationController &aContext);
  simulation::SimulationController &context;
};

}

#endif //PRODUCTION_LINE_CONTROL_CONTROLLERSTATE_H
