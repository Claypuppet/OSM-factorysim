//
// Created by klei on 4/23/18.
//

#include "SimulationState.h"

namespace simulationstates {

SimulationState::SimulationState(simulator::SimulationController &aContext)
	: context(aContext) {

}

bool SimulationState::handleEvent(const EventPtr &e) {
  switch (e->getId()) {
	default:
	  return false;
  }
}

}
