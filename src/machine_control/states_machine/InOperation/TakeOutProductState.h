
#ifndef PRODUCTION_LINE_CONTROL_TAKEOUTPRODUCTSTATE_H
#define PRODUCTION_LINE_CONTROL_TAKEOUTPRODUCTSTATE_H

#include "../MachineState.h"

namespace machinestates {

/**
 * Machine state to place a proccessed product into the buffer of the next machine in de production line
 */
class TakeOutProductState : public MachineState {
 public:
  TakeOutProductState(machinecore::Machine &aContext);
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
} // machinestates

#endif //PRODUCTION_LINE_CONTROL_TAKEOUTPRODUCTSTATE_H
