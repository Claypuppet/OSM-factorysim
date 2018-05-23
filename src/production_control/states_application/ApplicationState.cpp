//
// Created by klei on 5/3/18.
//

#include "ApplicationState.h"

namespace applicationstates {
ApplicationState::ApplicationState(core::Application &application) : context(application) {}

bool ApplicationState::handleEvent(const applicationstates::EventPtr &e) {
  return false;
}

}