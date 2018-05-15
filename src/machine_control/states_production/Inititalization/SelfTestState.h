//
// Created by sven on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SELFTESTSTATE_H
#define PRODUCTION_LINE_CONTROL_SELFTESTSTATE_H

#include "../ProductionState.h"

namespace productionstates {
class SelfTestState : public ProductionState {
 public:
  SelfTestState(machinecore::Application &aContext) : ProductionState(aContext) {};

  virtual ~SelfTestState() = default;

  virtual void entryAction();

  virtual void doActivity();

  virtual void exitAction();
};

}

#endif //PRODUCTION_LINE_CONTROL_SELFTESTSTATE_H
