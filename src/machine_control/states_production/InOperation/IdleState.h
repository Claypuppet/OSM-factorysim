//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_IDLESTATE_H
#define PRODUCTION_LINE_CONTROL_IDLESTATE_H

#include "../ProductionState.h"
#include "InOperationState.h"

namespace productionstates {
class IdleState : public InOperationState {
 public:
  IdleState(machinecore::Application &aContext) : InOperationState(aContext) {};

  virtual ~IdleState() = default;

  virtual void entryAction();

  virtual void doActivity();

  virtual void exitAction();
};
}

#endif //PRODUCTION_LINE_CONTROL_IDLESTATE_H
