
#ifndef PRODUCTION_LINE_CONTROL_REPAIRINGSTATE_H
#define PRODUCTION_LINE_CONTROL_REPAIRINGSTATE_H

#include "../ProductionState.h"

namespace productionstates {
class RepairingState : public ProductionState {
 public:
  RepairingState(machinecore::Application &aContext);
  virtual ~RepairingState() = default;

  virtual bool handleEvent(const EventPtr &event);
  virtual void entryAction();
  virtual void doActivity();
  virtual void exitAction();

 private:
  void onRepairFinishedEvent();
};

}

#endif //PRODUCTION_LINE_CONTROL_REPAIRINGSTATE_H
