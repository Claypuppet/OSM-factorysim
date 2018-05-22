//
// Created by bas on 15-5-18.
//

#include <utils/Logger.h>
#include "InOperationState.h"

ApplicationStates::InOperationState::InOperationState(core::Application &context) :
	ApplicationState(context) {
}

void ApplicationStates::InOperationState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.prepareScheduler();
}

void ApplicationStates::InOperationState::doActivity() {
  context.executeScheduler();
}

void ApplicationStates::InOperationState::exitAction() {

}

bool ApplicationStates::InOperationState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
	case ApplicationStates::kEventTypeMachineStatusUpdate:
	  utils::Logger::log("-Handle event: kEventTypeMachineStatusUpdate");
	  context.setMachineStatus(event->getArgumentAsType<uint16_t>(0),
							   event->getArgumentAsType<core::Machine::MachineStatus>(1));
	  return true;
	default: {
	  return ApplicationState::handleEvent(event);
	}
  }
}