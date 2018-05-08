
// standard libraries
#include <memory>

// libraries
#include <patterns/statemachine/Event.h>

// other
#include "utils/CommandLineArguments.h"
#include "FindProductControlState.h"
#include "ConnectSimulationState.h"

namespace simulationstates {

void FindProductControlState::entryAction() {

  // Create an event to signify receiving the IP-address
  EventPtr event = std::make_shared<Event>(Event(kEventTypeReceivedPCIP));

  // Get the "pcip" commandline argument from the given commandline arguments
  const utils::CommandlineArgument &pcip = utils::CommandLineArguments::getInstance().getKwarg("pcip");

  // Set the pcip value as the event's argument
  event->setArgument<std::string>(pcip.value)

  // Schedule the event to continue through the statemachine
  context.scheduleEvent(event);
}

void FindProductControlState::doActivity() {
}

void FindProductControlState::exitAction() {
}

bool FindProductControlState::handleEvent(const EventPtr &e) {

  switch (e->getId()) {
    case kEventTypeReceivedPCIP:onReceivedPCIP(e);
      return true;
    default: return SimulationState::handleEvent(e);
  }
}

void FindProductControlState::onReceivedPCIP(const EventPtr &e) {
  // Set remoteHost of context to the event's argument
  context.setRemoteHost(e->getArgumentAsType<std::string>());

  // Set context's current state to ConnectSimulation
  context.setCurrentState(std::make_shared<ConnectSimulationState>(context));
}
} // namespace simulationstates
