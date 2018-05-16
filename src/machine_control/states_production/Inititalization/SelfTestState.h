
#ifndef PRODUCTION_LINE_CONTROL_SELFTESTSTATE_H
#define PRODUCTION_LINE_CONTROL_SELFTESTSTATE_H

#include "../ProductionState.h"

namespace productionstates {

/**
 * State class that executes the self test for a machine
 */
class SelfTestState : public ProductionState {
 public:
  SelfTestState(machinecore::Application &aContext);
  virtual ~SelfTestState() = default;

  void entryAction() override;

  /**
   * Runs the self test and creates a new event depending on the result
   */
  void doActivity() override;
  void exitAction() override;
  bool handleEvent(const EventPtr &event) override;

 private:
  /**
   * Run the selftest
   * @return a boolean that tells if the selftest succeeded
   */
  bool executeSelfTest();

  /**
   * Runs if there was a selfTestSucceeded event
   */
  void onSelfTestSuccess();

  /**
   * Runs if there was a selfTestNotSucceded event
   */
  void onSelfTestFail();
};

}

#endif //PRODUCTION_LINE_CONTROL_SELFTESTSTATE_H
