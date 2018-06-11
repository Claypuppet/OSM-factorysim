//
// Created by klei on 6/10/18.
//

#ifndef PRODUCTION_LINE_CONTROL_PREPARESHUTDOWNSTATE_H
#define PRODUCTION_LINE_CONTROL_PREPARESHUTDOWNSTATE_H

#include "../InOperationState.h"

namespace applicationstates {

/**
 * State where the application will prepare for shutdown. all machines next action will be set to idle
 */
class PrepareShutdownState : public InOperationState {
 public:
  PrepareShutdownState(core::Application &context);
  ~PrepareShutdownState() override = default;

  void entryAction() override;
  void doActivity() override;
  void exitAction() override;
  bool handleEvent(const applicationstates::EventPtr &event) override;

  /**
   * All machines are disconnected, ready to shutdown for real.
   */
  void onAllMachinesDisconnected();
};

}

#endif //PRODUCTION_LINE_CONTROL_PREPARESHUTDOWNSTATE_H
