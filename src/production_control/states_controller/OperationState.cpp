//
// Created by don on 24-4-18.
//

#include "OperationState.h"

namespace States {

	OperationState::OperationState(simulation::SimulationController &context) : ControllerState(context) {}

	void OperationState::entryAction() {
//	    context.application->setStartState();
	}

	void OperationState::doActivity() {
//	    context.application->run();
	}

	void OperationState::exitAction() {
//		context.application.stop()
	}

	bool OperationState::handleEvent(const EventPtr &e) {
		return false;
	}

}