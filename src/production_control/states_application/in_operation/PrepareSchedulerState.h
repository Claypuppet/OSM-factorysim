//
// Created by klei on 6/10/18.
//

#ifndef PRODUCTION_LINE_CONTROL_PREPARESCHEDULERSTATE_H
#define PRODUCTION_LINE_CONTROL_PREPARESCHEDULERSTATE_H

#include "../InOperationState.h"

namespace applicationstates {

/**
 * State where the scheduler will be prepared. First state in the operation cycle after startup
 */
class PrepareSchedulerState : public InOperationState {
 public:
  PrepareSchedulerState(core::Application &aContext);
  ~PrepareSchedulerState() override = default;
  void entryAction() override;
  void doActivity() override;
  void exitAction() override;
  bool handleEvent(const EventPtr &event) override;

 private:
  /**
   * Start the day off with a change in production
   * @param $event
   */
  void onProductionChange(const EventPtr &event);

  /**
   * Can start the scheduler
   */
  void onCanSchedule();
};

}

#endif //PRODUCTION_LINE_CONTROL_PREPARESCHEDULERSTATE_H
