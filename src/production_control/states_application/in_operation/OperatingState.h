//
// Created by klei on 6/10/18.
//

#ifndef PRODUCTION_LINE_CONTROL_OPERATINGSTATE_H
#define PRODUCTION_LINE_CONTROL_OPERATINGSTATE_H

#include "../InOperationState.h"

namespace applicationstates {

/**
 * Default operation state where the scheduler is executed.
 */
class OperatingState : public InOperationState {
 public:
  OperatingState(core::Application &context);
  ~OperatingState() override = default;

  void entryAction() override;
  void doActivity() override;
  void exitAction() override;
  bool handleEvent(const applicationstates::EventPtr &event) override;
};

}

#endif //PRODUCTION_LINE_CONTROL_OPERATINGSTATE_H
