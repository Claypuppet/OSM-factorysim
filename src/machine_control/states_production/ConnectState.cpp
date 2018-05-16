//
// Created by sven on 23-4-18.
//

#include <utils/Logger.h>
#include "ConnectState.h"
#include "ReceiveConfig.h"

namespace productionstates {
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
      utils::Logger::log("-Handle event: kEventTypeConnected");
      context.setCurrentState(std::make_shared<ReceiveConfig>(context));
      break;
    }
    default:return false;
  }
}
}