
#include "FinishedOperationState.h"

namespace states {

FinishedOperationState::FinishedOperationState(simulation::SimulationController &context)
    : ControllerState(context) {
}

bool FinishedOperationState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    default:return ControllerState::handleEvent(event);
  }
}

void FinishedOperationState::doActivity() {

}

void FinishedOperationState::entryAction() {

}

void FinishedOperationState::exitAction() {

}

}