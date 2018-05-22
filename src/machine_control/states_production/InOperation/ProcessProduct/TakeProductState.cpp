
#include "TakeProductState.h"

#include <utils/Logger.h>

#include "ProcessProductState.h"

namespace productionstates {

void TakeProductState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.statusUpdate(models::Machine::kMachineStatusTakingProduct);
}

void TakeProductState::doActivity() {
  context.takeProductIn(); // TODO : This method is currently empty because we have no buffer model yet.
}

void TakeProductState::exitAction() {

}

bool TakeProductState::handleEvent(const EventPtr &event) {
  switch(event->getId()) {
    case kEventTypeProcessProduct:
      onProcessProductEvent();
      return true;

    default:
      return ProductionState::handleEvent(event);
  }
}

void TakeProductState::onProcessProductEvent() {
  utils::Logger::log("-Handle event: kEventTypeProcessProduct");

  auto processProductState = std::make_shared<ProcessProductState>(context);
  context.setCurrentState(processProductState);
}

}