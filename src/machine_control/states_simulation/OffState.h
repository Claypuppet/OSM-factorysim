//
// Created by klei on 4/23/18.
//

#ifndef PRODUCTION_LINE_CONTROL_OFFSTATE_H
#define PRODUCTION_LINE_CONTROL_OFFSTATE_H

#include "SimulationState.h"

namespace simulationstates {

/**
 * State in which the simulation finds itself when it is off
 */
class OffState : public SimulationState {
 public:
  OffState(simulator::SimulationController &context) : SimulationState(context) {};
  virtual ~OffState() = default;

  void entryAction() override;

  void doActivity() override;

  void exitAction() override;

  bool handleEvent(const EventPtr &event) override;
};
} // simulationstates

#endif //PRODUCTION_LINE_CONTROL_OFFSTATE_H
