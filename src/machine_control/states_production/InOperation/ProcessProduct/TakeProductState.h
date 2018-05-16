
#ifndef PRODUCTION_LINE_CONTROL_TAKEPRODUCTSTATE_H
#define PRODUCTION_LINE_CONTROL_TAKEPRODUCTSTATE_H

#include "../../../NetworkComponent.h"
#include "../../ProductionState.h"
#include "../InOperationState.h"

namespace productionstates {

class TakeProductState : public InOperationState {
 public:
  TakeProductState(machinecore::Application &aContext) : InOperationState(aContext) {};
  virtual ~TakeProductState() = default;

  bool handleEvent(const EventPtr &event);
  void entryAction();
  void doActivity();
  void exitAction();

 private:
  void onProcessProductEvent();

};
        
}

#endif //PRODUCTION_LINE_CONTROL_TAKEPRODUCTSTATE_H
