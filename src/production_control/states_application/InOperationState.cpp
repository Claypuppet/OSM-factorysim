//
// Created by bas on 15-5-18.
//

#include "InOperationState.h"

ApplicationStates::InOperationState::InOperationState(core::Application &context) :
    ApplicationState(context) {
}

void ApplicationStates::InOperationState::doActivity() {
  // Run scheduler here after implementation
}

void ApplicationStates::InOperationState::entryAction() {

}

void ApplicationStates::InOperationState::exitAction() {

}

bool ApplicationStates::InOperationState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    default:
      return ApplicationState::handleEvent(event);
  }
}