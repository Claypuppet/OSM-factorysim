//
// Created by klei on 4/23/18.
//

#include "OnState.h"
#include "OffState.h"

namespace simulationstates {
void OnState::entryAction() {
  context.getApplication().setStartState();
}

void OnState::doActivity() {
  context.getApplication().run();
}

void OnState::exitAction() {

}

bool OnState::handleEvent(const EventPtr &e) {
  switch (e->getId()) {
    case kEventTypePowerOff:context.setCurrentState(std::make_shared<OffState>(context));
      return true;
    default:return SimulationState::handleEvent(e);
  }
}
} // simulationstates