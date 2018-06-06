
#include <utils/Logger.h>
#include "FinishedOperationState.h"

namespace states {

FinishedOperationState::FinishedOperationState(simulation::SimulationController &context)
    : ControllerState(context) {
}

void FinishedOperationState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.stop();
}

void FinishedOperationState::doActivity() {

}

void FinishedOperationState::exitAction() {

}

bool FinishedOperationState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    default:return ControllerState::handleEvent(event);
  }
}

}