//
// Created by klei on 4/23/18.
//

#include "InitializeSimulationState.h"


namespace SimulationStates {
	void InitializeSimulationState::entryAction() {
		context.setupNetwork();
	}

	void InitializeSimulationState::doActivity() {
		if(context.isConnected()){
			auto e = std::make_shared<Event>(1);
			context.scheduleEvent(e);
		}
	}

	void InitializeSimulationState::exitAction() {

	}

	bool InitializeSimulationState::handleEvent(const EventPtr &e) {
		return SimulationState::handleEvent(e);
	}
}
