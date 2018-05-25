//
// Created by hqnders on 24/05/18.
//

#ifndef PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H

#include "ApplicationState.h"

namespace applicationstates {

/**
 * Applicationstate that controls the production-cycle of the machine
 */
class InOperationState : public ApplicationState {
 public:
  InOperationState(machinecore::Application &aContext);
  ~InOperationState() = default;

  void entryAction() override;
  void doActivity() override;
  void exitAction() override;
  bool handleEvent(const EventPtr &event) override;

 private:
  /**
   * Called when the production-cycle finishes without problem
   */
  void onFinishedProcessing();

  /**
   * Called when the machine broke down during production
   */
  void onMachineBroke();
};
} // applicationstates

#endif //PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H
