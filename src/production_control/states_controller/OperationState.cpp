
#include "OperationState.h"

namespace States {

	OperationState::OperationState(simulation::SimulationController &context) : ControllerState(context) {}

	void OperationState::entryAction() {
	  context.getApplication().setStartState();
	}

	void OperationState::doActivity() {
		context.getApplication().run();
	}

	void OperationState::exitAction() {
//		context.application.stop()
	}

	bool OperationState::handleEvent(const EventPtr &event) {
		return false;
	}

}