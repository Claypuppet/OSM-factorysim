
#ifndef PRODUCTION_LINE_CONTROL_TAKEOUTPRODUCTSTATE_H
#define PRODUCTION_LINE_CONTROL_TAKEOUTPRODUCTSTATE_H

#include "../../ProductionState.h"
#include "../InOperationState.h"

namespace productionstates {

class TakeOutProductState : public InOperationState {
 public:
  TakeOutProductState(machinecore::Application &aContext);
  virtual ~TakeOutProductState() = default;

  virtual void entryAction();
  virtual void doActivity();
  virtual void exitAction();
  bool handleEvent(const EventPtr event);

 private:
  void onProductTakenOutEvent();
};

}

#endif //PRODUCTION_LINE_CONTROL_TAKEOUTPRODUCTSTATE_H
