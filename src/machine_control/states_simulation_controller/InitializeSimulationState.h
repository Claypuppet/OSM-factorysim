//
// Created by klei on 4/23/18.
//

#ifndef PRODUCTION_LINE_CONTROL_INITIALIZESIMULATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_INITIALIZESIMULATIONSTATE_H

#include "SimulationState.h"

namespace simulationstates {

/**
 * State in which Machine Control gives it's ID to Production Control, which in turn returns it simulation configurations.
 */
class InitializeSimulationState : public SimulationState {
 public:
  InitializeSimulationState(simulator::SimulationController &context) : SimulationState(context) {};
  virtual ~InitializeSimulationState() = default;

  void entryAction() override;

  void doActivity() override;

  void exitAction() override;

  bool handleEvent(const EventPtr &event) override;

 private:
  /**
   * Function to execute on receiving simulation configurations, gives them to context.
   * @param event Event containing the configurations as it's first parameter
   */
  void onSimulationConfigurationsReceived(const EventPtr &event);

  /**
   * Handles event that is fired after configurations have been set.
   * @param event Event containing the configurations as it's first parameter
   */
  void onSimulationConfigurationsSet(const EventPtr &event);
};

}

#endif //PRODUCTION_LINE_CONTROL_INITIALIZESIMULATIONSTATE_H
