
#include "BrokenState.h"

#include <utils/Logger.h>
#include <utils/time/Time.h>

#include "ConfigureState.h"

namespace applicationstates {
BrokenState::BrokenState(machinecore::Application &aContext)
    : ApplicationState(aContext) {

}

void BrokenState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.machineBroke();
}

void BrokenState::doActivity() {
  context.startReparation();
}

void BrokenState::exitAction() {

}

bool BrokenState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeRepaired: {
      onRepairedEvent();
      return true;
    }

    default: {
      return ApplicationState::handleEvent(event);
    }
  }
}

void BrokenState::onRepairedEvent() {
  utils::Logger::log("-Handle event: kEventTypeRepaired");

  auto state = std::make_shared<ConfigureState>(context);
  context.setCurrentState(state);
}
} // applicationstates
