//
// Created by don on 24-4-18.
//

#include <utils/Logger.h>
#include "BroadCastState.h"

applicationstates::BroadCastState::BroadCastState(core::Application &context) : ApplicationState(context) {

}

void applicationstates::BroadCastState::doActivity() {

}

void applicationstates::BroadCastState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);

}

void applicationstates::BroadCastState::exitAction() {

}

bool applicationstates::BroadCastState::handleEvent(const EventPtr &e) {
  return false;
}
