
#ifndef PRODUCTION_LINE_CONTROL_BROKENSTATE_H
#define PRODUCTION_LINE_CONTROL_BROKENSTATE_H

#include "ApplicationState.h"

namespace applicationstates {

/**
 * Machine state when it gets repaired
 */
class BrokenState : public ApplicationState {
 public:
  BrokenState(machinecore::Application &aContext);
  virtual ~BrokenState() = default;

  virtual bool handleEvent(const EventPtr &event) override;
  virtual void entryAction();
  virtual void doActivity();
  virtual void exitAction();

 private:
  /**
   * Gets executed when a repair started event is coming in
   */
  void onRepairedEvent();
};
} // applicationstates

#endif //PRODUCTION_LINE_CONTROL_BROKENSTATE_H
