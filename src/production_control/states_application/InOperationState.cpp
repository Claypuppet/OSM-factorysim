//
// Created by bas on 15-5-18.
//

#include <utils/Logger.h>
#include "InOperationState.h"

applicationstates::InOperationState::InOperationState(core::Application &context) :
	ApplicationState(context) {
}

void applicationstates::InOperationState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.prepareScheduler();
}

void applicationstates::InOperationState::doActivity() {
  context.executeScheduler();
}

void applicationstates::InOperationState::exitAction() {

}

bool applicationstates::InOperationState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
	case applicationstates::kEventTypeMachineStatusUpdate:
	  onMachineStatusUpdateEvent(event);
	  return true;

	default: {
	  return ApplicationState::handleEvent(event);
	}
  }
}

void applicationstates::InOperationState::onMachineStatusUpdateEvent(const EventPtr &event) {
//	utils::Logger::log("-Handle event: kEventTypeMachineStatusUpdate");
	context.setMachineStatus(event->getArgumentAsType<uint16_t>(0),
							 event->getArgumentAsType<core::Machine::MachineStatus>(1));
}