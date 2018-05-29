//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_APPLICATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_APPLICATIONSTATE_H

#include <patterns/statemachine/State.h>

namespace applicationstates {

/**
 * Abstract state for application states
 */
class ApplicationState : public patterns::statemachine::State {
 public:
  ApplicationState() = default;
  bool handleEvent(const patterns::statemachine::EventPtr &event) override;
};

}
#endif //PRODUCTION_LINE_CONTROL_APPLICATIONSTATE_H
