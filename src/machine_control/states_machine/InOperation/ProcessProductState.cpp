
#include "ProcessProductState.h"

#include <utils/Logger.h>

#include "TakeOutProductState.h"

namespace machinestates {

ProcessProductState::ProcessProductState(machinecore::Machine &aContext)
	: MachineState(aContext) {
}

void ProcessProductState::entryAction() {
//  utils::Logger::log(__PRETTY_FUNCTION__);
}

void ProcessProductState::doActivity() {
  MachineState::doActivity();
  context.processProduct();
}

void ProcessProductState::exitAction() {

}

bool ProcessProductState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
	case kEventTypeProductProcessed: {
      onProductFinishedEvent();
      return true;
    }

	default: {
      MachineState::handleEvent(event);
    }
  }
}

void ProcessProductState::onProductFinishedEvent() {
//  utils::Logger::log("-Handle event: kEventTypeProductProcessed");

  auto state = std::make_shared<TakeOutProductState>(context);
  context.setCurrentState(state);
}
} // machinestates