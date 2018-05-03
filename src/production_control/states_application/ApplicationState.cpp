//
// Created by klei on 5/3/18.
//

#include "ApplicationState.h"

namespace ApplicationStates {
	ApplicationState::ApplicationState(Core::Application &context) : context(context) {}

	bool ApplicationState::handleEvent(const ApplicationStates::EventPtr &e) {
		return false;
	}

}