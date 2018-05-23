
#ifndef PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H

#include "../ProductionState.h"

namespace productionstates {

/**
 * Parrent state for machine product processing states
 */
class InOperationState : public ProductionState {
 public:
  InOperationState(machinecore::Application &aContext);
  virtual ~InOperationState() = default;

  virtual bool handleEvent(const EventPtr &event) override;

 private:

  /**
   * Gets executed everytime a machineBrokeDown event is received
   */
  void onMachineBrokenDownEvent();
};

}
#endif //PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H
