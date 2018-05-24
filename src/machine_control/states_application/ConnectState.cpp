//
// Created by sven on 23-4-18.
//

#include <utils/Logger.h>
#include "ConnectState.h"
#include "Initialize.h"

namespace applicationstates {

ConnectState::ConnectState(machinecore::Application &aContext) : ApplicationState(aContext) {

}

void ConnectState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.setupNetwork();
}

void ConnectState::doActivity() {

}

void ConnectState::exitAction() {

}

bool ConnectState::handleEvent(const patterns::statemachine::EventPtr &event) {
  switch (event->getId()) {
	case kEventTypeConnected: {
	  onConnected();
	  break;
	}
	default:
	  return false;
  }
}

void ConnectState::onConnected() {
  utils::Logger::log("-Handle event: kEventTypeConnected");
  context.setCurrentState(std::make_shared<Initialize>(context));
}
} // applicationstates