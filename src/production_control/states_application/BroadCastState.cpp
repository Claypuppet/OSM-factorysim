//
// Created by don on 24-4-18.
//

#include <utils/Logger.h>
#include "BroadCastState.h"

ApplicationStates::BroadCastState::BroadCastState(core::Application &context) : ApplicationState(context) {

}

void ApplicationStates::BroadCastState::doActivity() {

}

void ApplicationStates::BroadCastState::entryAction() {
    utils::Logger::log(__PRETTY_FUNCTION__);

}

void ApplicationStates::BroadCastState::exitAction() {

}

bool ApplicationStates::BroadCastState::handleEvent(const EventPtr &e) {
    return false;
}
