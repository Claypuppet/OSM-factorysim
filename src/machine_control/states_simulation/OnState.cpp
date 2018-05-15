//
// Created by klei on 4/23/18.
//

#include <utils/Logger.h>
#include "OnState.h"
#include "OffState.h"

namespace simulationstates {

void OnState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.getApplication().setStartState();
}

void OnState::doActivity() {
  context.getApplication().run();
}

void OnState::exitAction() {

}

<<<<<<<
HEAD
bool OnState::handleEvent(const EventPtr &e) {
  switch (e->getId()) {
    case kEventTypePowerOff:context.setCurrentState(std::make_shared<OffState>(context));
      return true;
    default:return SimulationState::handleEvent(e);
  }
}
} // simulationstates
=======
bool OnState::handleEvent(const EventPtr &e) {
  switch (e->getId()) {
    case kEventTypePowerOff: utils::Logger::log("-Handle event: kEventTypePowerOff");
      context.setCurrentState(std::make_shared<OffState>(context));
      return true;
    default:return SimulationState::handleEvent(e);
  }
}
}
>>>>>>> 1a61f256fa3156ba74f8a646d46820de914bcaeb
