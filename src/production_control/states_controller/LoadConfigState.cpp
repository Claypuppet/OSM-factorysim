//
// Created by don on 24-4-18.
//

#include <iostream>
#include <utils/Logger.h>

#include "LoadConfigState.h"

#include "SimulationBroadcastState.h"
#include "OperationState.h"

namespace states {
LoadConfigState::LoadConfigState(simulation::SimulationController &context) : ControllerState(context) {}

bool LoadConfigState::handleEvent(const EventPtr &e) {
  switch (e->getId()) {
	case kEventTypeReadConfigFile:
	  utils::Logger::log("-Handle event: kEventTypeReadConfigFile");
	  context.setConfigFromFile(e->getArgumentAsType<std::string>());
	  break;
	case kEventTypeSimulationConfigLoaded:
	  utils::Logger::log("-Handle event: kEventTypeSimulationConfigLoaded");
	  context.setCurrentState(std::make_shared<SimulationBroadcastState>(context));
	  break;
	case kEventTypeProductionConfigLoaded:
	  utils::Logger::log("-Handle event: kEventTypeProductionConfigLoaded");
	  context.setCurrentState(std::make_shared<OperationState>(context));
	  break;
	default:
	  return ControllerState::handleEvent(e);
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