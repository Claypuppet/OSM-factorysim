//
// Created by klei on 4/23/18.
//

#include "ConnectSimulationState.h"
#include "InitializeSimulationState.h"
#include "WaitForProductControlState.h"

namespace simulationstates {
void ConnectSimulationState::entryAction() {
  context.setupNetwork();
}

void ConnectSimulationState::doActivity() {
}

void ConnectSimulationState::exitAction() {

}

bool ConnectSimulationState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeConnectionFailed: context.setCurrentState(std::make_shared<WaitForProductControlState>(context));
      return true;
    case kEventTypeConnected:context.setCurrentState(std::make_shared<InitializeSimulationState>(context));
      return true;
    default: return SimulationState::handleEvent(event);
  }
}
}
