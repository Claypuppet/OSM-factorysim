
// standard libraries
#include <memory>

// libraries
#include <patterns/statemachine/Event.h>
#include <utils/Logger.h>

// other
#include "utils/CommandLineArguments.h"
#include "FindProductControlState.h"
#include "ConnectSimulationState.h"
#include "WaitForProductControlState.h"

namespace simulationstates {

void FindProductControlState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);

}

void FindProductControlState::doActivity() {
  // Create an event to signify receiving the IP-address
  EventPtr event = std::make_shared<Event>(Event(kEventTypeReceivedPCIP));

  // Get the "pcip" commandline argument from the given commandline arguments
  const utils::CommandlineArgument &pcip = utils::CommandLineArguments::getInstance().getKwarg("-pcip");

  if (!pcip) {
    event->setArgument<std::string>(pcip.value);
  } else {
    event->setArgument<std::string>("localhost");
  }

  // Schedule the event to continue through the statemachine
  context.scheduleEvent(event);
}

void FindProductControlState::exitAction() {
}

bool FindProductControlState::handleEvent(const EventPtr &event) {

  switch (event->getId()) {
	case kEventTypeReceivedPCIP:
	  utils::Logger::log("-Handle event: kEventTypeReceivedPCIP");
	  onReceivedPCIP(event);
	  return true;
	case kEventTypeFailedToReceivePCIP:
	  utils::Logger::log("-Handle event: kEventTypeFailedToReceivePCIP");
	  onFailedToReceivePCIP();
	  return true;
	default:
	  return SimulationState::handleEvent(event);
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
