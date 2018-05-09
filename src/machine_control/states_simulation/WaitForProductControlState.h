//
// Created by hqnders on 09/05/18.
//

#ifndef PRODUCTION_LINE_CONTROL_WAITFORPRODUCTCONTROLSTATE_H
#define PRODUCTION_LINE_CONTROL_WAITFORPRODUCTCONTROLSTATE_H

#include "ConnectSimulationState.h"
#include "FindProductControlState.h"

namespace simulationstates {

class WaitForProductControlState : public SimulationState {
 public:
  WaitForProductControlState(simulator::SimulationController &context) : SimulationState(context) {};
  ~WaitForProductControlState() override = default;

  void entryAction() override;

  void doActivity() override;

  void exitAction() override;

  bool handleEvent(const EventPtr &e) override;
};
} // namespace simulationstates

#endif //PRODUCTION_LINE_CONTROL_WAITFORPRODUCTCONTROLSTATE_H
