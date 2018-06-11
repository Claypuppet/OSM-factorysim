//
// Created by klei on 6/10/18.
//

#include <utils/Logger.h>
#include "PreChangeState.h"
#include "OperatingState.h"

namespace applicationstates {

PreChangeState::PreChangeState(core::Application &context, uint16_t configId)
    : InOperationState(context), configId(configId) {

}

void PreChangeState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  // TODO: this not here lol
  context.changeProductionLineProduct(configId);
}

void PreChangeState::doActivity() {
  InOperationState::doActivity();

  // TODO: this not here either lol
  context.createAndScheduleStateEvent(kEventTypeCanSchedule);
}

void PreChangeState::exitAction() {

}

bool PreChangeState::handleEvent(const applicationstates::EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeCanSchedule: {
      onCanSchedule();
      return true;
    }
    default: {
      return InOperationState::handleEvent(event);
    }
  }
}

void PreChangeState::onCanSchedule() {
  context.setCurrentState(std::make_shared<OperatingState>(context));
}

}
