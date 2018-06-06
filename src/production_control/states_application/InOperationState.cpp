
#include "InOperationState.h"

#include <utils/Logger.h>

namespace applicationstates {

InOperationState::InOperationState(core::Application &context) :
		ApplicationState(context) {
}

void InOperationState::entryAction() {
	utils::Logger::log(__PRETTY_FUNCTION__);
	context.prepareScheduler();
}

void InOperationState::doActivity() {
	context.executeScheduler();
}

void InOperationState::exitAction() {

}

bool InOperationState::handleEvent(const EventPtr &event) {
	switch (event->getId()) {
		case applicationstates::kEventTypeMachineStatusUpdate: onMachineStatusUpdateEvent(event);
		return true;

		default: {
			return ApplicationState::handleEvent(event);
		}
	}
}

void InOperationState::onMachineStatusUpdateEvent(const EventPtr &event) {
//	utils::Logger::log("-Handle event: kEventTypeMachineStatusUpdate");
	context.setMachineStatus(event->getArgumentAsType<uint16_t>(0),
							 event->getArgumentAsType<core::Machine::MachineStatus>(1));
}

}