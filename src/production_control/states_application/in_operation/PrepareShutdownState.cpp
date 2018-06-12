//
// Created by klei on 6/10/18.
//

#include <utils/Logger.h>
#include "PrepareShutdownState.h"
#include "../ShutdownState.h"

namespace applicationstates {

PrepareShutdownState::PrepareShutdownState(core::Application &context) : InOperationState(context) {
}

void PrepareShutdownState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.prepareForShutdown();
}

void PrepareShutdownState::doActivity() {
  InOperationState::doActivity();
  context.checkAllMachinesDisconnected();
}

void PrepareShutdownState::exitAction() {
}

bool PrepareShutdownState::handleEvent(const applicationstates::EventPtr &event) {
  switch (event->getId()) {
    case applicationstates::kEventTypeWorkDayOver:
      // Do nothing because we're already in this state. no need to trigger this again
      return true;
    case applicationstates::kEventTypeMachineDisconnected:
      context.getMachine(event->getArgumentAsType<uint16_t>(0))->setStatus(core::Machine::kMachineStatusDisconnected);
      return true;
    case applicationstates::kEventTypeAllMachinesDisconnected:
      onAllMachinesDisconnected();
      return true;
    default: {
      return InOperationState::handleEvent(event);
    }
  }
}

void PrepareShutdownState::onAllMachinesDisconnected() {
  context.setCurrentState(std::make_shared<ShutdownState>(context));
}

}
