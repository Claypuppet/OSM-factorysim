
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
      onMachineReady(event);
      break;

    case kEventTypeAllMachinesReady:
      onAllMachinesReady();
      break;

    default:
      return ApplicationState::handleEvent(event);
  }
}

void ApplicationStates::WaitForConnectionsState::onMachineReady(const EventPtr &event) {
  context.setMachineStatusReady(event->getArgumentAsType<u_int16_t>(0));

  if (context.allMachinesReady()) {
    auto event = std::make_shared<Event>(kEventTypeAllMachinesReady);
    context.scheduleEvent(event);
  }
}

void ApplicationStates::WaitForConnectionsState::onAllMachinesReady() {
  // TODO : set the next state "InOperation.cpp" but this state has to be implemented first...
}