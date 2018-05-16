
#ifndef PRODUCTION_LINE_CONTROL_REPAIRINGSTATE_H
#define PRODUCTION_LINE_CONTROL_REPAIRINGSTATE_H

#include "../ProductionState.h"

namespace productionstates {

/**
 * Machine state when it is broken
 */
class RepairingState : public ProductionState {
 public:
  RepairingState(machinecore::Application &aContext);
  virtual ~RepairingState() = default;

  virtual bool handleEvent(const EventPtr &event);
  virtual void entryAction();
  virtual void doActivity();
  virtual void exitAction();

 private:

  /**
   * Gets executed when a repairFinished event is comming in
   */
  void onRepairFinishedEvent();
};

}

#endif //PRODUCTION_LINE_CONTROL_REPAIRINGSTATE_H
