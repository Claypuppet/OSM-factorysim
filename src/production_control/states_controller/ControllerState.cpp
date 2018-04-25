//
// Created by klei on 4/25/18.
//

#include "ControllerState.h"

namespace States {
	ControllerState::ControllerState(Core::SimulationController &context) : context(context) {}

	bool ControllerState::handleEvent(const States::EventPtr &e) {
		return false;
	}

}