//
// Created by klei on 4/23/18.
//

#include "OffState.h"
#include "OnState.h"

namespace SimulationStates {
	void OffState::entryAction() {

	}

	void OffState::doActivity() {

	}

	void OffState::exitAction() {

	}

	bool OffState::handleEvent(const EventPtr &e) {
		switch(e->getId()){
            case kEventTypePowerOn:
                context.setCurrentState(std::make_shared<OnState>(context));
            default:
                return SimulationState::handleEvent(e);
        }
	}

}