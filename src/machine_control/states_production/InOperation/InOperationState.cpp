
#include "InOperationState.h"

#include <utils/Logger.h>

#include "../Broken/BrokenState.h"

namespace productionstates {

InOperationState::InOperationState(machinecore::Application &aContext)
: ProductionState(aContext) {
}

bool InOperationState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeMachineBrokeDown:
      onMachineBrokenDownEvent();
      return true;

    default:return InOperationState::handleEvent(event);

  }
}

void InOperationState::onMachineBrokenDownEvent() {
  utils::Logger::log("-Handle event: kEventTypeMachineBrokeDown");

  auto brokenState = std::make_shared<BrokenState>(context);
  context.setCurrentState(brokenState);
}

}

