
#ifndef PRODUCTION_LINE_CONTROL_TAKEPRODUCTSTATE_H
#define PRODUCTION_LINE_CONTROL_TAKEPRODUCTSTATE_H

#include "../../../NetworkComponent.h"
#include "../../ProductionState.h"
#include "../InOperationState.h"

namespace productionstates {

/**
 * Machine state for taking a product out of a buffer
 */
class TakeProductState : public InOperationState {
 public:
  TakeProductState(machinecore::Application &aContext) : InOperationState(aContext) {};
  virtual ~TakeProductState() = default;

  virtual bool handleEvent(const EventPtr &event);
  virtual void entryAction();
  virtual void doActivity();
  virtual void exitAction();

 private:

  /**
   * Gets executed when a processProduct event is received
   */
  void onProcessProductEvent();

};

}

#endif //PRODUCTION_LINE_CONTROL_TAKEPRODUCTSTATE_H
