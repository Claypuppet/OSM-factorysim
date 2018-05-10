
#include "OperationState.h"

namespace States {

OperationState::OperationState(simulation::SimulationController &aContext)
    : ControllerState(aContext) {

}

void OperationState::entryAction() {
  context.getApplication().setStartState();
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