//
// Created by klei on 4/23/18.
//

#include <utils/Logger.h>
#include "OffState.h"
#include "OnState.h"

namespace simulationstates {
	void OffState::entryAction() {
	  utils::Logger::log(__PRETTY_FUNCTION__);

	}

	void OffState::doActivity() {

	}

	void OffState::exitAction() {

	}

	bool OffState::handleEvent(const EventPtr &event) {
		switch(event->getId()){
            case kEventTypePowerOn:
			    utils::Logger::log("-Handle event: kEventTypePowerOn");
                context.setCurrentState(std::make_shared<OnState>(context));
                return true;
            default:
                return SimulationState::handleEvent(event);
        }
	}
} // simulationstates