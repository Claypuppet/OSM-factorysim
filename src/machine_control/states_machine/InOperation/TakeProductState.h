
#ifndef PRODUCTION_LINE_CONTROL_TAKEPRODUCTSTATE_H
#define PRODUCTION_LINE_CONTROL_TAKEPRODUCTSTATE_H

#include "../MachineState.h"

namespace machinestates {

/**
 * Machine state for taking a product out of a buffer
 */
class TakeProductState : public MachineState {
 public:
  TakeProductState(machinecore::Machine &aContext);
  ~TakeProductState() override = default;

  bool handleEvent(const EventPtr &event) override;
  void entryAction() override;
  void doActivity() override;
  void exitAction() override;

 private:
  /**
   * Gets executed when a processProduct event is received
   */
  void onProcessProductEvent();
};
} // machinestates

#endif //PRODUCTION_LINE_CONTROL_TAKEPRODUCTSTATE_H
