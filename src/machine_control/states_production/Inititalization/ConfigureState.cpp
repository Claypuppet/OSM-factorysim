//
// Created by sven on 23-4-18.
//

#include <utils/Logger.h>
#include "ConfigureState.h"
#include "SelfTestState.h"

namespace productionstates {
void ConfigureState::entryAction() {
  context.setCurrentConfig();
}

void ConfigureState::doActivity() {

}

void ConfigureState::exitAction() {

}

bool ConfigureState::handleEvent(const patterns::statemachine::EventPtr &e) {
  switch (e->getId()) {
    case kEventTypeConfigured: {
      context.setCurrentState(std::make_shared<SelfTestState>(context));
      break;
    }
    default:return false;
  }
}

}