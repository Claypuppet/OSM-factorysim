
#include "TakeOutProductState.h"

#include <utils/Logger.h>

#include "../../states_application/IdleState.h"

namespace machinestates {

TakeOutProductState::TakeOutProductState(machinecore::Machine &aContext)
    : MachineState(aContext) {
}

void TakeOutProductState::entryAction() {
//  utils::Logger::log(__PRETTY_FUNCTION__);
}

void TakeOutProductState::doActivity() {
  context.takeOutProduct();
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

  auto notification =
      patterns::notifyobserver::NotifyEvent(machinecore::NotifyEventType::kNotifyEventTypeMachineFinishedProcess);
  context.notifyObservers(notification);
}
} // machinestates