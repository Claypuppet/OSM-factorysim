//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_LOADCONFIGSTATE_H
#define PRODUCTION_LINE_CONTROL_LOADCONFIGSTATE_H

#include "ControllerState.h"

namespace states {
class LoadConfigState : public ControllerState {
 public:
  LoadConfigState(simulation::SimulationController &context);
  bool handleEvent(const EventPtr &event) override;

  /**
   * Loads configuration and creates machine objects for the Application and SimulationController class
   */
  void doActivity() override;

  void entryAction() override;

  void exitAction() override;

};
}

#endif //PRODUCTION_LINE_CONTROL_LOADCONFIGSTATE_H
