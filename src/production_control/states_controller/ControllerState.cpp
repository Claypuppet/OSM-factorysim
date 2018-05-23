
#include "ControllerState.h"

namespace states {

ControllerState::ControllerState(simulation::SimulationController &aContext)
	: context(aContext) {

}

bool ControllerState::handleEvent(const states::EventPtr &event) {
  return false;
}

}
