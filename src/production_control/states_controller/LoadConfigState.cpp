
#include <iostream>
#include <utils/Logger.h>

#include "LoadConfigState.h"

#include "SimulationBroadcastState.h"
#include "OperationState.h"

namespace states {

LoadConfigState::LoadConfigState(simulation::SimulationController &context)
		: ControllerState(context) {
}

bool LoadConfigState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
	case kEventTypeReadConfigFile:
	  utils::Logger::log("-Handle event: kEventTypeReadConfigFile");
      context.setConfiguration(event->getArgumentAsType<std::string>());
	  return true;

	case kEventTypeSimulationConfigLoaded:
	  utils::Logger::log("-Handle event: kEventTypeSimulationConfigLoaded");
	  context.setCurrentState(std::make_shared<SimulationBroadcastState>(context));
	  return true;

	case kEventTypeProductionConfigLoaded:
	  utils::Logger::log("-Handle event: kEventTypeProductionConfigLoaded");
	  context.setCurrentState(std::make_shared<OperationState>(context));
	  return true;

	case kEventTypeLocalSimulationConfigLoaded:
	  utils::Logger::log("-Handle event: kEventTypeLocalSimulationConfigLoaded");
	  context.setCurrentState(std::make_shared<OperationState>(context));
	  return true;

	default:
	  return ControllerState::handleEvent(event);
  }
}

void LoadConfigState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
}

void LoadConfigState::doActivity() {
}

void LoadConfigState::exitAction() {
}

}