//
// Created by klei on 6/10/18.
//

#include <utils/Logger.h>
#include "OperatingState.h"

namespace applicationstates {

OperatingState::OperatingState(core::Application &context) : InOperationState(context) {
}

void OperatingState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
}

void OperatingState::doActivity() {
  InOperationState::doActivity();
}

void OperatingState::exitAction() {
}

bool OperatingState::handleEvent(const applicationstates::EventPtr &event) {
  switch (event->getId()) {
    default: {
      return InOperationState::handleEvent(event);
    }
  }
}

}
