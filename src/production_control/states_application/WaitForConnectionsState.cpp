
#include <utils/Logger.h>
#include "WaitForConnectionsState.h"
#include "InOperationState.h"

ApplicationStates::WaitForConnectionsState::WaitForConnectionsState(core::Application &context) :
        ApplicationState(context) {
}

void ApplicationStates::WaitForConnectionsState::doActivity() {

}

void ApplicationStates::WaitForConnectionsState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.setupNetwork();
}

void ApplicationStates::WaitForConnectionsState::exitAction() {

}

bool ApplicationStates::WaitForConnectionsState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeMachineRegistered:
      utils::Logger::log("-Handle event: kEventTypeMachineRegistered");
      onMachineRegistered(event);
      break;

    case kEventTypeAllMachinesRegistered:
      utils::Logger::log("-Handle event: kEventTypeAllMachinesRegistered");
      onAllMachinesConnected();
      break;

    default:
      return ApplicationState::handleEvent(event);
  }
}

void ApplicationStates::WaitForConnectionsState::onMachineRegistered(const EventPtr &event) {
  context.registerMachine(event->getArgumentAsType<u_int16_t>(0), event->getArgumentAsType<Network::ConnectionPtr>(1));

}

void ApplicationStates::WaitForConnectionsState::onAllMachinesConnected() {
  context.setCurrentState(std::make_shared<InOperationState>(context));
}
