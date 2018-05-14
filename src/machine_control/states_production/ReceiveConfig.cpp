//
// Created by sven on 9-5-18.
//

#include "ReceiveConfig.h"
#include "Inititalization/ConfigureState.h"

namespace ProductionStates {
void ReceiveConfig::entryAction() {
  context.setupNetwork();
}

void ReceiveConfig::doActivity() {

}

void ReceiveConfig::exitAction() {

}

bool ReceiveConfig::handleEvent(const Patterns::Statemachine::EventPtr &e) {
  switch (e->getId()) {
    case kEventTypeConnected: {
      context.setCurrentState(std::make_shared<ConfigureState>(context));
      break;
    }
    default:return false;
  }
}
}