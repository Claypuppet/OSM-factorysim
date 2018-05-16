//
// Created by sven on 23-4-18.
//

#include <utils/Logger.h>
#include "BrokenState.h"

namespace productionstates {
BrokenState::BrokenState(machinecore::Application &aContext)
    : ProductionState(aContext) {

}

void BrokenState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);

}

void BrokenState::doActivity() {

}

void BrokenState::exitAction() {

}
bool BrokenState::handleEvent(const patterns::statemachine::EventPtr &e) {
  return false;
}

}
