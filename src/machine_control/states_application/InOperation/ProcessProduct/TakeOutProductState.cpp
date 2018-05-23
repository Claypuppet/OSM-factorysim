
#include "TakeOutProductState.h"

#include <utils/Logger.h>

#include "../IdleState.h"

namespace productionstates {

TakeOutProductState::TakeOutProductState(machinecore::Application &aContext)
	: InOperationState(aContext) {
}

void TakeOutProductState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.statusUpdate(models::Machine::kMachineStatusTakingOutProduct);
}

void TakeOutProductState::doActivity() {
  context.takeProductOut(); // TODO : method is empty because no product is processed yet.
}

void TakeOutProductState::exitAction() {

}

bool TakeOutProductState::handleEvent(const productionstates::EventPtr &event) {
  switch (event->getId()) {
	case kEventTypeProductTakenOut:
	  onProductTakenOutEvent();
	  return true;

	default:
	  return InOperationState::handleEvent(event);
  }
}

void TakeOutProductState::onProductTakenOutEvent() {
  utils::Logger::log("-Handle event: kEventTypeProductTakenOut");

  auto idleState = std::make_shared<IdleState>(context);
  context.setCurrentState(idleState);
}

}