//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONBROADCASTSTATE_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONBROADCASTSTATE_H

#include "ControllerState.h"

namespace states {
class SimulationBroadcastState : public ControllerState {
 public:
  SimulationBroadcastState(simulation::SimulationController &context);

  /**
   * Broadcasts the ip and port over the network
   */
  void doActivity() override;

  bool handleEvent(const EventPtr &e) override;

  void entryAction() override;

  void exitAction() override;
};
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONBROADCASTSTATE_H
