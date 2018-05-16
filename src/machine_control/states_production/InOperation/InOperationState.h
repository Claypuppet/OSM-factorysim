
#ifndef PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H

#include "../ProductionState.h"

namespace productionstates {

class InOperationState : public ProductionState {
 public:
  InOperationState(machinecore::Application &aContext);
  virtual ~InOperationState() = default;

  bool handleEvent(const EventPtr &event) override;

 private:
  void onMachineBrokenDownEvent();
};

}
#endif //PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H
