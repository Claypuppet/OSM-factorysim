
#include "TakeProductState.h"

#include <utils/Logger.h>

#include "ProcessProductState.h"

namespace machinestates {

TakeProductState::TakeProductState(machinecore::Machine &aContext) : MachineState(aContext) {

}

void TakeProductState::entryAction() {
//  utils::Logger::log(__PRETTY_FUNCTION__);
}

void TakeProductState::doActivity() {
  if(!context.checkBroken()){
    context.takeInProduct();
  }
}

void TakeProductState::exitAction() {

}

bool TakeProductState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeProductTakenIn: {
      onProcessProductEvent();
      return true;
    }

    default: {
      return MachineState::handleEvent(event);
    }
  }
}

void TakeProductState::onProcessProductEvent() {
//  utils::Logger::log("-Handle event: kEventTypeProductTakenIn");

  auto state = std::make_shared<ProcessProductState>(context);
  context.setCurrentState(state);
}
} // machinestates