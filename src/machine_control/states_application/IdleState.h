
#ifndef PRODUCTION_LINE_CONTROL_IDLESTATE_H
#define PRODUCTION_LINE_CONTROL_IDLESTATE_H

#include "ApplicationState.h"

namespace applicationstates {

/**
 * Machine state for waiting on a process product command
 */
class IdleState : public ApplicationState {
 public:
  IdleState(machinecore::Application &aContext);
  virtual ~IdleState() = default;

  bool handleEvent(const EventPtr &event) override;
  void entryAction() override;
  void doActivity() override;
  void exitAction() override;

 private:

  /**
   * Gets executed everytime a receivedConfig event is received
   */
  void onReceivedConfigEvent(const EventPtr &event);

  /**
   * gets executed everytime a takeProduct event in received
   */
  void onStartProcessing();
};
} // applicationstates

#endif //PRODUCTION_LINE_CONTROL_IDLESTATE_H
