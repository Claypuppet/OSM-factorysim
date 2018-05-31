
#ifndef PRODUCTION_LINE_CONTROL_OPERATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_OPERATIONSTATE_H

// project file includes
#include "ControllerState.h"

namespace states {
class OperationState : public ControllerState {
 public:
  OperationState(simulation::SimulationController &aContext);

  /**
   * Runs the simulation
   */
  void doActivity() override;
  void entryAction() override;
  bool handleEvent(const EventPtr &event) override;
  void exitAction() override;

<<<<<<< HEAD
 private:
  // Log every hour, next moment is after this.
  uint64_t logMoment;


 private:
  void onSimulationFinished();
=======
>>>>>>> b907fb7eb187f25e20d8d56e8a0625e97bae39a2
};
}

#endif //PRODUCTION_LINE_CONTROL_OPERATIONSTATE_H
