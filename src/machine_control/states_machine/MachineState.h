//
// Created by hqnders on 23/05/18.
//

#ifndef PRODUCTION_LINE_CONTROL_MACHINESTATES_H
#define PRODUCTION_LINE_CONTROL_MACHINESTATES_H

#include "patterns/statemachine/State.h"
#include "../Machine.h"

namespace machinestates {

enum EventType {
  kEventTypeReconfigure,
  kEventTypeConfigured,
  kEventTypeSelfTestSuccess,
  kEventTypeSelfTestFailed,
  kEventTypeMachineBroke,
  kEventTypeTakeProduct,
  kEventTypeProcessProduct,
  kEventTypeFinishedProduct,
  kEventTypeProductTakenOut,
};

typedef patterns::statemachine::Event Event;
typedef patterns::statemachine::EventPtr EventPtr;

/**
 * MachineState is the base state for all machinestates
 */
class MachineState : public patterns::statemachine::State {
 public:
  virtual ~MachineState() = default;

  void entryAction() override = 0;
  void doActivity() override = 0;
  void exitAction() override = 0;
  bool handleEvent(const EventPtr &event) override;

 protected:
  MachineState(machinecore::Machine &aContext);

  machinecore::Machine &context;
};
} // machinestates

#endif //PRODUCTION_LINE_CONTROL_MACHINESTATES_H
