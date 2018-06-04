
#ifndef PRODUCTION_LINE_CONTROL_SELFTESTSTATE_H
#define PRODUCTION_LINE_CONTROL_SELFTESTSTATE_H

#include "../MachineState.h"

namespace machinestates {

/**
 * State class that executes the self test for a machine
 */
class SelfTestState : public MachineState {
 public:
  SelfTestState(machinecore::Machine &aContext);
  virtual ~SelfTestState() = default;

  void entryAction() override;
  void doActivity() override;
  void exitAction() override;
  bool handleEvent(const EventPtr &event) override;

 private:
  /**
   * Runs if there was a selfTestSucceeded event
   */
  void onSelfTestSuccess();

  /**
   * Runs if there was a selfTestNotSucceded event
   */
  void onSelfTestFail();
};
} // machinestates

#endif //PRODUCTION_LINE_CONTROL_SELFTESTSTATE_H
