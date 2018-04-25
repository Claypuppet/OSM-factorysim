
#include "InitializeSimulationState.h"
#include "OffState.h"

namespace SimulationStates {
	void InitializeSimulationState::entryAction() {
		// TODO: Register machine
	}

	void InitializeSimulationState::doActivity() {
	}

	void InitializeSimulationState::exitAction() {
		// TODO: Set config? but the config is in the event? hmmm
	}

	bool InitializeSimulationState::handleEvent(const EventPtr &e) {
		switch (e->getId()){
			case kEventTypeConfigReceived:
				context.setCurrentState(std::make_shared<OffState>(context));
			default:
				return SimulationState::handleEvent(e);
		}
	}
}
