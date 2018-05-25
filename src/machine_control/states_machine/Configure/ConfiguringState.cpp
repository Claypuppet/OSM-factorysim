//
// Created by sven on 23-4-18.
//

#include "ConfiguringState.h"

#include <utils/Logger.h>
#include "SelfTestState.h"

namespace machinestates {

void ConfiguringState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
}

void ConfiguringState::doActivity() {
  MachineState::doActivity();
  context.configure();
}

void ConfiguringState::exitAction() {

}

bool ConfiguringState::handleEvent(const patterns::statemachine::EventPtr &event) {
  switch (event->getId()) {
	case kEventTypeConfigured: {
	  onConfigured();
	  return true;
	}

	default: {
      return MachineState::handleEvent(event);
    }
  }
}

void ConfiguringState::onConfigured() {
  utils::Logger::log("-Handle event: kEventTypeConfigured");

  auto state = std::make_shared<SelfTestState>(context);
  context.setCurrentState(state);
}
} // machinestates