
// standard libraries
#include <memory>

// libraries
#include <patterns/statemachine/Event.h>

// other
#include "utils/CommandLineArguments.h"
#include "FindProductControlState.h"
#include "ConnectSimulationState.h"
#include "WaitForProductControlState.h"

namespace simulationstates {

void FindProductControlState::entryAction() {

  // Create an event to signify receiving the IP-address
  EventPtr event = std::make_shared<Event>(Event(kEventTypeReceivedPCIP));

  // Get the "pcip" commandline argument from the given commandline arguments
  const utils::CommandlineArgument &pcip = utils::CommandLineArguments::getInstance().getKwarg("-pcip");

  // Set the pcip value as the event's argument
  event->setArgument<std::string>(pcip.value);

  // Schedule the event to continue through the statemachine
  context.scheduleEvent(event);
}

void FindProductControlState::doActivity() {
}

void FindProductControlState::exitAction() {
}

bool FindProductControlState::handleEvent(const EventPtr &event) {

  switch (event->getId()) {
    case kEventTypeReceivedPCIP:onReceivedPCIP(event);
      return true;
    case kEventTypeFailedToReceivePCIP:onFailedToReceivePCIP();
      return true;
    default:return SimulationState::handleEvent(event);
  }
}

void FindProductControlState::onReceivedPCIP(const EventPtr &event) {
  // Set remoteHost of context to the event's argument
  context.setRemoteHost(event->getArgumentAsType<std::string>());

  // Set context's current state to ConnectSimulation
  context.setCurrentState(std::make_shared<ConnectSimulationState>(context));
}

void FindProductControlState::onFailedToReceivePCIP() {

  // Set context's current state to WaitForProductControl
  context.setCurrentState(std::make_shared<WaitForProductControlState>(context));
}
} // namespace simulationstates
