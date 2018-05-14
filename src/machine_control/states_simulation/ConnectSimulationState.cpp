//
// Created by klei on 4/23/18.
//

#include "ConnectSimulationState.h"
#include "InitializeSimulationState.h"


namespace simulationstates {
	void ConnectSimulationState::entryAction() {
		context.setupNetwork();
	}

	void ConnectSimulationState::doActivity() {
	}

	void ConnectSimulationState::exitAction() {

	}

	bool ConnectSimulationState::handleEvent(const EventPtr &e) {
		switch (e->getId()){
			case kEventTypeConnectionFailed:
				// TODO: create WaitForProductionControl state and listen to udp
				return true;
			case kEventTypeConnected:
				context.setCurrentState(std::make_shared<InitializeSimulationState>(context));
				return true;
			default:
				return SimulationState::handleEvent(e);
		}
	}
}
