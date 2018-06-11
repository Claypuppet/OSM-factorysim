//
// Created by klei on 6/10/18.
//

#include <utils/Logger.h>
#include "PrepareSchedulerState.h"
#include "OperatingState.h"
#include "PreChangeState.h"

namespace applicationstates {

PrepareSchedulerState::PrepareSchedulerState(core::Application &aContext) : InOperationState(aContext) {
}

void PrepareSchedulerState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.prepareScheduler();
}

void PrepareSchedulerState::doActivity() {
  InOperationState::doActivity();
}

void PrepareSchedulerState::exitAction() {
}

bool PrepareSchedulerState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case applicationstates::kEventTypeProductionChange:
      onProductionChange(event);
      return true;
    case applicationstates::kEventTypeCanSchedule:
      onCanSchedule();
      return true;
    default: {
      return InOperationState::handleEvent(event);
    }
  }
}
void PrepareSchedulerState::onProductionChange(const EventPtr &event) {
  auto configId = event->getArgumentAsType<uint16_t>(0);
  context.setCurrentState(std::make_shared<PreChangeState>(context, configId));
}
void PrepareSchedulerState::onCanSchedule() {
  context.setCurrentState(std::make_shared<OperatingState>(context));
}

}
