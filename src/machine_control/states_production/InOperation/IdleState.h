
#ifndef PRODUCTION_LINE_CONTROL_IDLESTATE_H
#define PRODUCTION_LINE_CONTROL_IDLESTATE_H

#include "InOperationState.h"

namespace productionstates {

/**
 * Machine state for waiting on a process product command
 */
class IdleState : public InOperationState {
 public:
  IdleState(machinecore::Application &aContext);
  virtual ~IdleState() = default;

  virtual bool handleEvent(const EventPtr &event);
  virtual void entryAction();
  virtual void doActivity();
  virtual void exitAction();

 private:

  /**
   * Gets executed everytime a receivedConfig event is received
   */
  void onReceivedConfigEvent();

  /**
   * gets executed everytime a takeProduct event in received
   */
  void onTakeProductEvent();
};

}

#endif //PRODUCTION_LINE_CONTROL_IDLESTATE_H
