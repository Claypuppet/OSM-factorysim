
#include "OperationState.h"

namespace states {

OperationState::OperationState(simulation::SimulationController &aContext)
    : ControllerState(aContext) {

}

void OperationState::entryAction() {
  context.getApplication().setStartState();
  context.turnOnSimulationMachines();
}

void OperationState::doActivity() {
  context.getApplication().run();
}

void OperationState::exitAction() {
  // stop application
}

bool OperationState::handleEvent(const EventPtr &event) {
  return false;
}

}