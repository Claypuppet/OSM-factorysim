
#include "BrokenState.h"

#include <utils/Logger.h>

namespace productionstates {
BrokenState::BrokenState(machinecore::Application &aContext)
	: ProductionState(aContext) {

}

void BrokenState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);

}

void BrokenState::doActivity() {

}

void BrokenState::exitAction() {

}
bool BrokenState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
	case kEventTypeRepairStarted:
	  onRepairStartedEvent();
	  return true;

	default:
	  return ProductionState::handleEvent(event);
  }
}

void BrokenState::onRepairStartedEvent() {
  utils::Logger::log("-Handle event: kEventTypeRepairStarted");

  auto brokenState = std::make_shared<BrokenState>(context);
  context.setCurrentState(brokenState);
}

}
