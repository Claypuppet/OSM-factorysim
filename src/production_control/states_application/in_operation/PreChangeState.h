//
// Created by klei on 6/10/18.
//

#ifndef PRODUCTION_LINE_CONTROL_PREPARECHANGESTATE_H
#define PRODUCTION_LINE_CONTROL_PREPARECHANGESTATE_H

#include "../InOperationState.h"


namespace applicationstates {

/**
 * State where the scheduler will prepare to change the production to a different product. Makes sure that all
 * buffers are empty for the machines that have to change.
 */
class PreChangeState : public InOperationState {
 public:
  PreChangeState(core::Application &context, uint16_t configId);
  ~PreChangeState() override = default;

  void entryAction() override;
  void doActivity() override;
  void exitAction() override;
  bool handleEvent(const applicationstates::EventPtr &event) override;

 private:
  uint16_t configId;
  void onCanSchedule();
};

}

#endif //PRODUCTION_LINE_CONTROL_PREPARECHANGESTATE_H
