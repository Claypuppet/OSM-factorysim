//
// Created by sven on 23-4-18.
//

#include <utils/Logger.h>
#include "ConfigureState.h"

namespace productionstates {
void ConfigureState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);

}

void ConfigureState::doActivity() {

}

void ConfigureState::exitAction() {

}

bool ConfigureState::handleEvent(const patterns::statemachine::EventPtr &e) {
  return false;
}

}