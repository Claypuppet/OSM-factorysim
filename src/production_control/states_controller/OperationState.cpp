
#include <utils/Logger.h>
#include <utils/time/Time.h>
#include "OperationState.h"

namespace states {

OperationState::OperationState(simulation::SimulationController &aContext)
	: ControllerState(aContext){

}

void OperationState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.getApplication()->setStartState();
}

void OperationState::doActivity() {
  context.getApplication()->run();
}

void OperationState::exitAction() {
  // stop application
}

bool OperationState::handleEvent(const EventPtr &event) {
  return false;
}

}