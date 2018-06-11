//
// Created by klei on 6/10/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SHUTDOWNSTATE_H
#define PRODUCTION_LINE_CONTROL_SHUTDOWNSTATE_H

#include "InOperationState.h"

namespace applicationstates {

/**
 * State where all machines are disconnected. flushes day log and waits for new day to start
 */
class ShutdownState : public ApplicationState {
 public:
  ShutdownState(core::Application &application);
  ~ShutdownState() override = default;

  void entryAction() override;
  void doActivity() override;
  void exitAction() override;
  bool handleEvent(const EventPtr &e) override;

 private:
  /**
   * A new day has started!
   */
  void onNewWorkDayStarted();
};

}

#endif //PRODUCTION_LINE_CONTROL_SHUTDOWNSTATE_H
