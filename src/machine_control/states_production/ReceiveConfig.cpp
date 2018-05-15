//
// Created by sven on 9-5-18.
//

#include "ReceiveConfig.h"
#include "Inititalization/ConfigureState.h"

namespace productionstates {
void ReceiveConfig::entryAction() {
  context.setupNetwork();
}

void ReceiveConfig::doActivity() {

}

void ReceiveConfig::exitAction() {

}

bool ReceiveConfig::handleEvent(const patterns::statemachine::EventPtr &e) {
  switch (e->getId()) {
    case kEventTypeConnected: {
      context.setCurrentState(std::make_shared<ConfigureState>(context));
      break;
    }
    default:return false;
  }
}
}