//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_LIVESTATE_H
#define PRODUCTION_LINE_CONTROL_LIVESTATE_H

#include "../../../visualizer/application_states/ApplicationState.h"

namespace livefeedstates {

/**
 * Abstract state for live feed states
 */
class LiveState : public patterns::statemachine::State{
 public:
  LiveState() = default;
  bool handleEvent(const patterns::statemachine::EventPtr &e) override;
};

}

#endif //PRODUCTION_LINE_CONTROL_LIVESTATE_H
