
#ifndef PRODUCTION_LINE_CONTROL_FINISHOPERATION_H
#define PRODUCTION_LINE_CONTROL_FINISHOPERATION_H

#include "ControllerState.h"

namespace states {

/**
 * State that gets active when a simulation is finished
 */
class FinishedOperationState : public ControllerState {
 public:
  FinishedOperationState(simulation::SimulationController &context);
  virtual ~FinishedOperationState() = default;

  bool handleEvent(const EventPtr &event) override;
  void doActivity() override;
  void entryAction() override;
  void exitAction() override;

};

}

#endif //PRODUCTION_LINE_CONTROL_FINISHOPERATION_H
