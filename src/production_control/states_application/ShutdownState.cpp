//
// Created by klei on 6/10/18.
//

#include <utils/Logger.h>
#include "ShutdownState.h"
#include "WaitForConnectionsState.h"

namespace applicationstates {

ShutdownState::ShutdownState(core::Application &application) : ApplicationState(application) {
}

void ShutdownState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.workDayOver();
}

void ShutdownState::doActivity() {
  context.checkTimeToStartAgain();
}

void ShutdownState::exitAction() {
}

bool ShutdownState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeNewWorkDayStarted: {
      onNewWorkDayStarted();
    }
    default: {
      return ApplicationState::handleEvent(event);
    }
  }
}

void ShutdownState::onNewWorkDayStarted() {
  context.setCurrentState(std::make_shared<WaitForConnectionsState>(context));
}

}
