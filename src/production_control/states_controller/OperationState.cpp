
#include <utils/Logger.h>
#include <utils/time/Time.h>

#include "OperationState.h"
#include "FinishedOperationState.h"

namespace states {

OperationState::OperationState(simulation::SimulationController &aContext)
	: ControllerState(aContext), logMoment(0) {

}

void OperationState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.getApplication()->setStartState();
  uint64_t currentTime = utils::Time::getInstance().getCurrentTime();
  logMoment = currentTime;

  context.setSimulationEndTime();
}

void OperationState::doActivity() {
  context.getApplication()->run();

  if (context.simulationIsOver()) {
    auto event = std::make_shared<Event>(kEventTypeSimulationFinished);
    context.scheduleEvent(event);
  }
}

void OperationState::exitAction() {
  // stop application
}

bool OperationState::handleEvent(const EventPtr &event) {
  switch(event->getId()) {
    case kEventTypeSimulationFinished:
      onSimulationFinished();
      return true;

    default:
      return ControllerState::handleEvent(event);
  }
}

void OperationState::onSimulationFinished() {
  context.setCurrentState(std::make_shared<FinishedOperationState>(context));
}

}