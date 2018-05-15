//
// Created by sven on 7-5-18.
//

#include "InOperationState.h"
#include "../Broken/BrokenState.h"

namespace productionstates {
bool InOperationState::handleEvent(const EventPtr &e) {
  switch (e->getId()) {
    case kMachineBrokeDown: {
      auto brokenState = std::make_shared<BrokenState>(BrokenState(context));

      context.setCurrentState(brokenState);
      return true;

    }
    default:return InOperationState::handleEvent(e);

  }
}
}

