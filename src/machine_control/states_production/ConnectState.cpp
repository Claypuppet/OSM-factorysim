//
// Created by sven on 23-4-18.
//

#include "ConnectState.h"
#include "Inititalization/ConfigureState.h"

namespace ProductionStates {
void ConnectState::entryAction() {
  context.setupNetwork();
}

void ConnectState::doActivity() {

}

void ConnectState::exitAction() {

}

bool ConnectState::handleEvent(const Patterns::Statemachine::EventPtr &e) {
  switch (e->getId()) {
    case kEventTypeConnected: {
      context.setCurrentState(std::make_shared<ConfigureState>(context));
      break;
    }
    default:return false;
  }
}
}