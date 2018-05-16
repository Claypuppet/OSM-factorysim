
#include "ProcessProductState.h"

#include <utils/Logger.h>

#include "TakeOutProductState.h"

namespace productionstates {

ProcessProductState::ProcessProductState(machinecore::Application &aContext)
: InOperationState(aContext) {
}

void ProcessProductState::entryAction() {

}

void ProcessProductState::doActivity() {
  context.processProduct(); // TODO : method is currently empty because the product can't be taken in yet
}

void ProcessProductState::exitAction() {

}

bool ProcessProductState::handleEvent(const EventPtr event) {
  switch(event->getId()) {
    case kEventTypeFinishedProduct:
      onProductFinishedEvent();
      return true;

    default:
      InOperationState::handleEvent(event);
  }
}

void ProcessProductState::onProductFinishedEvent() {
  utils::Logger::log("-Handle event: kEventTypeFinishedProduct");
  context.setCurrentState(std::make_shared<TakeOutProductState>(context));
}

}
