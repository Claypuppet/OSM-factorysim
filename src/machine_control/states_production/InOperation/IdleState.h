
#ifndef PRODUCTION_LINE_CONTROL_IDLESTATE_H
#define PRODUCTION_LINE_CONTROL_IDLESTATE_H

#include "../ProductionState.h"
#include "../ProductionState.h"

namespace productionstates {

class IdleState : public ProductionState {
 public:
  IdleState(machinecore::Application &aContext);
  virtual ~IdleState() = default;

  bool handleEvent(const EventPtr &event);
  void entryAction();
  void doActivity();
  void exitAction();

 private:
  void onReceivedConfigEvent();
};

}

#endif //PRODUCTION_LINE_CONTROL_IDLESTATE_H
