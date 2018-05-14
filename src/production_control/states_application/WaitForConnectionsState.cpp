
#include "WaitForConnectionsState.h"

ApplicationStates::WaitForConnectionsState::WaitForConnectionsState(core::Application &context) :
        ApplicationState(context) {
}

void ApplicationStates::WaitForConnectionsState::doActivity() {

}

void ApplicationStates::WaitForConnectionsState::entryAction() {

}

void ApplicationStates::WaitForConnectionsState::exitAction() {

}

bool ApplicationStates::WaitForConnectionsState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeMachineReady:
      onMachineRegistered(event);
      break;

    case kEventTypeAllMachinesReady:
      onAllMachinesReady();
      break;

    default:
      return ApplicationState::handleEvent(event);
  }
}

void ApplicationStates::WaitForConnectionsState::onMachineRegistered(const EventPtr &event) {
  context.setMachineStatusReady(event->getArgumentAsType<u_int16_t>(0));

  if (context.allMachinesReady()) {
    auto event = std::make_shared<Event>(kEventTypeAllMachinesReady);
    context.scheduleEvent(event);
  }
}

void ApplicationStates::WaitForConnectionsState::onAllMachinesReady() {
  // set new state...
}