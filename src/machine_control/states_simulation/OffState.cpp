//
// Created by klei on 4/23/18.
//

#include "OffState.h"


namespace SimulationStates {
	void OffState::entryAction() {

	}

	void OffState::doActivity() {

	}

	void OffState::exitAction() {

	}

	bool OffState::handleEvent(const EventPtr &e) {
		return SimulationState::handleEvent(e);
	}

}