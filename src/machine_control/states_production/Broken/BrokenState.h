//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_BROKENSTATE_H
#define PRODUCTION_LINE_CONTROL_BROKENSTATE_H

#include "../ProductionState.h"

namespace ProductionStates {
class BrokenState : public ProductionState {
 public:
  BrokenState(machinecore::Application &aContext);
  virtual bool handleEvent(const patterns::statemachine::EventPtr &e);

  virtual ~BrokenState() = default;

  virtual void entryAction();

  virtual void doActivity();

  virtual void exitAction();
};

}

#endif //PRODUCTION_LINE_CONTROL_BROKENSTATE_H
