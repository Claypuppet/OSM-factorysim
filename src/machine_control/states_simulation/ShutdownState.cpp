//
// Created by klei on 4/23/18.
//

#include "ShutdownState.h"


namespace SimulationStates {
	void ShutdownState::entryAction() {

	}

	void ShutdownState::doActivity() {

	}

	void ShutdownState::exitAction() {

	}

	bool ShutdownState::handleEvent(const EventPtr &e) {
		return SimulationState::handleEvent(e);
	}
}