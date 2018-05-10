
#include "ControllerState.h"

namespace States {

ControllerState::ControllerState(simulation::SimulationController &aContext)
    : context(aContext) {

}

bool ControllerState::handleEvent(const States::EventPtr &event) {
  return false;
}

}
