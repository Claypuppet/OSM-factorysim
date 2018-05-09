//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H
#define PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H

#include "../../ProductionState.h"
#include "../InOperationState.h"

namespace ProductionStates {
class ProcessProductState : public InOperationState {
 public:
  ProcessProductState(machinecore::Application &aContext) : InOperationState(aContext) {};

  virtual ~ProcessProductState() = default;

  virtual void entryAction();

  virtual void doActivity();

  virtual void exitAction();
};

}

#endif //PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H
