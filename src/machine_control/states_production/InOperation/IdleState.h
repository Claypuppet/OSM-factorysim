
#ifndef PRODUCTION_LINE_CONTROL_IDLESTATE_H
#define PRODUCTION_LINE_CONTROL_IDLESTATE_H

#include "InOperationState.h"

namespace productionstates {

class IdleState : public InOperationState {
 public:
  IdleState(machinecore::Application &aContext);
  virtual ~IdleState() = default;

  bool handleEvent(const EventPtr &event);
  void entryAction();
  void doActivity();
  void exitAction();

 private:
  void onReceivedConfigEvent();
  void onTakeProductEvent();
};

}

#endif //PRODUCTION_LINE_CONTROL_IDLESTATE_H
