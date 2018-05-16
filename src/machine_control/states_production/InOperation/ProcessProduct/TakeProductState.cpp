
#include "TakeProductState.h"

#include <utils/Logger.h>

#include "ProcessProductState.h"

namespace productionstates {

void TakeProductState::entryAction() {

}

void TakeProductState::doActivity() {
  context.takeProductIn(); // TODO : This method is not implemented yet
}

void TakeProductState::exitAction() {

}

bool TakeProductState::handleEvent(const EventPtr event) {
  switch(event->getId()) {
    case kEventTypeProcessProduct:
      onProcessProductEvent();

    default:
      ProductionState::handleEvent(event);
  }
}

void TakeProductState::onProcessProductEvent() {
  utils::Logger::log("-Handle event: kEventTypeProcessProduct");
  context.setCurrentState(std::make_shared<ProcessProductState>(context));
}

}