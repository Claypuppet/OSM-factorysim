//
// Created by klei on 4/23/18.
//

#ifndef PRODUCTION_LINE_CONTROL_ONSTATE_H
#define PRODUCTION_LINE_CONTROL_ONSTATE_H

#include "SimulationState.h"

namespace simulationstates {
/**
 * State in which Machine Control is "on" and simulating
 */
class OnState : public SimulationState {
 public:
  OnState(simulator::SimulationController &context) : SimulationState(context) {};
  virtual ~OnState() = default;

  void entryAction() override;

  void doActivity() override;

  void exitAction() override;

  bool handleEvent(const EventPtr &event) override;

};
} // simulationstates

#endif //PRODUCTION_LINE_CONTROL_ONSTATE_H
