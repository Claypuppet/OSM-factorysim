
#include <utils/Logger.h>
#include "WaitForConnectionsState.h"
#include "InOperationState.h"

applicationstates::WaitForConnectionsState::WaitForConnectionsState(core::Application &context) :
	ApplicationState(context) {
}

void applicationstates::WaitForConnectionsState::doActivity() {

}

void applicationstates::WaitForConnectionsState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.setupNetwork();
}

void applicationstates::WaitForConnectionsState::exitAction() {

}

bool applicationstates::WaitForConnectionsState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
	case kEventTypeMachineRegistered:
	  utils::Logger::log("-Handle event: kEventTypeMachineRegistered");
	  onMachineRegistered(event);
	  break;

	case kEventTypeAllMachinesRegistered:
	  utils::Logger::log("-Handle event: kEventTypeAllMachinesRegistered");
	  onAllMachinesConnected();
	  break;

	default:
	  return ApplicationState::handleEvent(event);
  }
}

void applicationstates::WaitForConnectionsState::onMachineRegistered(const EventPtr &event) {
  context.registerMachine(event->getArgumentAsType<u_int16_t>(0), event->getArgumentAsType<network::ConnectionPtr>(1));

}

void applicationstates::WaitForConnectionsState::onAllMachinesConnected() {
  context.setCurrentState(std::make_shared<InOperationState>(context));
}
