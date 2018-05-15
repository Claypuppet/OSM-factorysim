//
// Created by bas on 15-5-18.
//

#include "InOperationState.h"

ApplicationStates::InOperationState::InOperationState(core::Application &context) :
    ApplicationState(context) {
}

void ApplicationStates::InOperationState::doActivity() {

}

void ApplicationStates::InOperationState::entryAction() {

}

void ApplicationStates::InOperationState::exitAction() {

}

bool ApplicationStates::InOperationState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {

    // TODO : implement the right states

    default:
      return ApplicationState::handleEvent(event);
  }
}