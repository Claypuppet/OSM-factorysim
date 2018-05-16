
#ifndef PRODUCTION_LINE_CONTROL_IDLESTATE_H
#define PRODUCTION_LINE_CONTROL_IDLESTATE_H

#include "InOperationState.h"

namespace productionstates {

class IdleState : public InOperationState {
 public:
  IdleState(machinecore::Application &aContext);
  virtual ~IdleState() = default;

  virtual bool handleEvent(const EventPtr &event);
  virtual void entryAction();
  virtual void doActivity();
  virtual void exitAction();

 private:
  void onReceivedConfigEvent();
  void onTakeProductEvent();
};

}

#endif //PRODUCTION_LINE_CONTROL_IDLESTATE_H
