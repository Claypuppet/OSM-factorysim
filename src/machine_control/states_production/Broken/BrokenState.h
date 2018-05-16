
#ifndef PRODUCTION_LINE_CONTROL_BROKENSTATE_H
#define PRODUCTION_LINE_CONTROL_BROKENSTATE_H

#include "../ProductionState.h"

namespace productionstates {

class BrokenState : public ProductionState {
 public:
  BrokenState(machinecore::Application &aContext);
  virtual ~BrokenState() = default;

  virtual bool handleEvent(const EventPtr &event) override;
  virtual void entryAction();
  virtual void doActivity();
  virtual void exitAction();

 private:
  void onRepairStartedEvent();
};

}

#endif //PRODUCTION_LINE_CONTROL_BROKENSTATE_H
