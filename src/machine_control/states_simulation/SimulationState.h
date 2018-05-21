//
// Created by klei on 4/23/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONSTATE_H

#include <patterns/statemachine/State.h>
#include <patterns/statemachine/Event.h>
#include "../SimulationController.h"

namespace simulationstates {

enum EventType {
  kEventTypeReceivedPCIP,
  kEventTypeFailedToReceivePCIP,
  kEventTypeConnected,
  kEventTypeConnectionFailed,
  kEventTypeSimulationConfigurationsReceived,
  kEventTypeSimulationConfigurationsSet,
  kEventTypePowerOn,
  kEventTypePowerOff,
//			kEventType,
};

typedef patterns::statemachine::Event Event;
typedef patterns::statemachine::EventPtr EventPtr;

class SimulationState : public patterns::statemachine::State {

 public:
  virtual ~SimulationState() = default;
  virtual bool handleEvent(const EventPtr &e);
  virtual void entryAction() = 0;
  virtual void doActivity() = 0;
  virtual void exitAction() = 0;
 protected:
  SimulationState(simulator::SimulationController &);
  simulator::SimulationController &context;

};
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONSTATE_H
