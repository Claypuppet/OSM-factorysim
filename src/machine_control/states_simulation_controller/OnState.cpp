//
// Created by klei on 4/23/18.
//

#include <utils/Logger.h>
#include "OnState.h"
#include "OffState.h"

namespace simulationstates {

void OnState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.getApplication()->setStartState();
}

void OnState::doActivity() {
  context.getApplication()->run();
}

void OnState::exitAction() {
  // Disconnect the application
  context.getApplication()->stopClient();
}

bool OnState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypePowerOff:
      utils::Logger::log("-Handle event: kEventTypePowerOff");
      context.setCurrentState(std::make_shared<OffState>(context));
      return true;
    default:
      return SimulationState::handleEvent(event);
  }
}
} // simulationstates
