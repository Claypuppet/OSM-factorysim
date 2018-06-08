
#include "TakeOutProductState.h"

#include <utils/Logger.h>

namespace machinestates {

TakeOutProductState::TakeOutProductState(machinecore::Machine &aContext)
    : MachineState(aContext) {
}

void TakeOutProductState::entryAction() {
//  utils::Logger::log(__PRETTY_FUNCTION__);
}

void TakeOutProductState::doActivity() {
  if(!context.checkBroken()){
    context.takeOutProduct();
  }
}

void TakeOutProductState::exitAction() {

}

bool TakeOutProductState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeProductTakenOut: {
      onProductTakenOutEvent();
      return true;
    }

    default: {
      return MachineState::handleEvent(event);
    }
  }
}

void TakeOutProductState::onProductTakenOutEvent() {
//  utils::Logger::log("-Handle event: kEventTypeProductTakenOut");
  auto notification = context.makeNotifcation(machinecore::NotifyEventType::kNotifyEventTypeMachineFinishedProcess);
  context.notifyObservers(notification);
}
} // machinestates