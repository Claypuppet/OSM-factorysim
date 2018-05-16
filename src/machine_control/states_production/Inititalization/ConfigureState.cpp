//
// Created by sven on 23-4-18.
//

#include <utils/Logger.h>
#include "ConfigureState.h"
#include "SelfTestState.h"

namespace productionstates {
void ConfigureState::entryAction() {
  context.setCurrentConfig();
  utils::Logger::log(__PRETTY_FUNCTION__);
}

void ConfigureState::doActivity() {

}

void ConfigureState::exitAction() {

}

bool ConfigureState::handleEvent(const patterns::statemachine::EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeConfigured: {
      context.setCurrentState(std::make_shared<SelfTestState>(context));
      break;
    }
    default:return false;
  }
}
}