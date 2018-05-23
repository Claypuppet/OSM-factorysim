
#ifndef PRODUCTION_LINE_CONTROL_TAKEOUTPRODUCTSTATE_H
#define PRODUCTION_LINE_CONTROL_TAKEOUTPRODUCTSTATE_H

#include "../../ProductionState.h"
#include "../InOperationState.h"

namespace productionstates {

/**
 * Machine state to place a proccessed product into the buffer of the next machine in de production line
 */
class TakeOutProductState : public InOperationState {
 public:
  TakeOutProductState(machinecore::Application &aContext);
  virtual ~TakeOutProductState() = default;

  virtual void entryAction();
  virtual void doActivity();
  virtual void exitAction();
  virtual bool handleEvent(const EventPtr &event);

 private:

  /**
   * Gets executed when a productTakenOut event is received
   */
  void onProductTakenOutEvent();
};

}

#endif //PRODUCTION_LINE_CONTROL_TAKEOUTPRODUCTSTATE_H
