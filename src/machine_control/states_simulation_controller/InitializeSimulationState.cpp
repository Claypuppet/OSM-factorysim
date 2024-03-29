#include <utils/Logger.h>
#include "InitializeSimulationState.h"
#include "OffState.h"
#include "models/Configuration.h"

namespace simulationstates {

void InitializeSimulationState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.registerMachine();
}

void InitializeSimulationState::doActivity() {
}

void InitializeSimulationState::exitAction() {
  context.machineReady();
}

bool InitializeSimulationState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
	case kEventTypeSimulationConfigurationsReceived: {
	  utils::Logger::log("-Handle event: kEventTypeSimulationConfigurationsReceived");
	  onSimulationConfigurationsReceived(event);
	  return true;
	}
	case kEventTypeSimulationConfigurationsSet: {
	  utils::Logger::log("-Handle event: kEventTypeSimulationConfigurationsSet");
	  onSimulationConfigurationsSet(event);
	  return true;
	}
	default:
	  return SimulationState::handleEvent(event);
  }
}

void InitializeSimulationState::onSimulationConfigurationsReceived(const simulationstates::EventPtr &event) {
  auto machine = event->getArgumentAsType<models::MachinePtr>();
  context.setMachineInfo(machine);
}

void InitializeSimulationState::onSimulationConfigurationsSet(const simulationstates::EventPtr &event) {
  context.setCurrentState(std::make_shared<OffState>(context));
}
}
