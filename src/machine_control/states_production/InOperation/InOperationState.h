//
// Created by sven on 7-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H

#include "../ProductionState.h"

namespace ProductionStates {
class InOperationState : public ProductionState {
 public:
  InOperationState(machinecore::Application &aContext) : ProductionState(aContext) {};
  bool handleEvent(const EventPtr &e) override;
};
}
#endif //PRODUCTION_LINE_CONTROL_INOPERATIONSTATE_H
