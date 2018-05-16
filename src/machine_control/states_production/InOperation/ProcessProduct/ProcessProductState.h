
#ifndef PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H
#define PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H

#include "../../ProductionState.h"
#include "../InOperationState.h"

namespace productionstates {

class ProcessProductState : public InOperationState {
 public:
  ProcessProductState(machinecore::Application &aContext);

  virtual ~ProcessProductState() = default;

  bool handleEvent(const EventPtr &event);
  void entryAction();
  void doActivity();
  void exitAction();

 private:
  void onProductFinishedEvent();
};

}

#endif //PRODUCTION_LINE_CONTROL_PROCESSPRODUCTSTATE_H
