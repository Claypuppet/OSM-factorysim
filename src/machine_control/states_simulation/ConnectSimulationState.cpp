//
// Created by klei on 4/23/18.
//

#include <utils/Logger.h>
#include "ConnectSimulationState.h"
#include "InitializeSimulationState.h"
#include "WaitForProductControlState.h"

namespace simulationstates {
void ConnectSimulationState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.setupNetwork();
}

void ConnectSimulationState::doActivity() {
}

void ConnectSimulationState::exitAction() {

}

bool ConnectSimulationState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeConnectionFailed:
      utils::Logger::log("-Handle event: kEventTypeConnectionFailed");
      context.setCurrentState(std::make_shared<WaitForProductControlState>(context));
      return true;
    case kEventTypeConnected:
      utils::Logger::log("-Handle event: kEventTypeConnected");
      context.setCurrentState(std::make_shared<InitializeSimulationState>(context));
      return true;
    default: return SimulationState::handleEvent(event);
  }
}
}
