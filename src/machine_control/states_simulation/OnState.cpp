//
// Created by klei on 4/23/18.
//

#include "OnState.h"
#include "../states_production/ConnectState.h"


namespace SimulationStates {
	void OnState::entryAction() {
	    context.getApplication().setCurrentState(std::make_shared<ProductionStates::ConnectState>(context));
	}

	void OnState::doActivity() {
        context.getApplication().run();
    }

	void OnState::exitAction() {

	}

	bool OnState::handleEvent(const EventPtr &e) {
		return SimulationState::handleEvent(e);
	}
}