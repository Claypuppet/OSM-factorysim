
// standard libraries
#include <memory>

// libraries
#include <patterns/statemachine/Event.h>

// other
#include "FindProductControlState.h"
#include "ConnectSimulationState.h"

namespace SimulationStates {
	void FindProductControlState::entryAction() {
		// For now, kei hard hardcoded ip address.
		EventPtr e = std::make_shared<Event>(Event(kEventTypeReceivedPCIP));
		e->setArgument<std::string>("127.0.0.1");
		context.scheduleEvent(e);
	}

	void FindProductControlState::doActivity() {
	}

	void FindProductControlState::exitAction() {
	}

	bool FindProductControlState::handleEvent(const EventPtr &e) {
		switch (e->getId()){
			case kEventTypeReceivedPCIP:
				context.setRemoteHost(e->getArgumentAsType<std::string>());
				context.setCurrentState(std::make_shared<ConnectSimulationState>(context));
				return true;
			default:
				return SimulationState::handleEvent(e);
		}
	}
}
