//
// Created by klei on 4/24/18.
//

#ifndef PRODUCTION_LINE_CONTROL_FINDPRODUCTCONTROLSTATE_H
#define PRODUCTION_LINE_CONTROL_FINDPRODUCTCONTROLSTATE_H

#include "SimulationState.h"

namespace simulationstates {

class FindProductControlState : public SimulationState {
 public:
  FindProductControlState(simulator::SimulationController &context) : SimulationState(context) {};
  virtual ~FindProductControlState() = default;

  void entryAction() override;

  void doActivity() override;

  void exitAction() override;

  bool handleEvent(const EventPtr &e) override;

 private:
  void onReceivedPCIP(const EventPtr &e);
};
}

#endif //PRODUCTION_LINE_CONTROL_FINDPRODUCTCONTROLSTATE_H
