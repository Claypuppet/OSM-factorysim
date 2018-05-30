
#include <utils/Logger.h>
#include <utils/time/Time.h>
#include "OperationState.h"

namespace states {

OperationState::OperationState(simulation::SimulationController &aContext)
	: ControllerState(aContext), logMoment(0) {

}

void OperationState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.getApplication()->setStartState();
  logMoment = utils::Time::getInstance().getCurrentTime();
}

void OperationState::doActivity() {
  context.getApplication()->run();

  // Log update?
  auto current = utils::Time::getInstance().getCurrentTime();
  if(utils::Time::getInstance().getCurrentTime() > logMoment){
    logMoment = utils::Time::getInstance().getCurrentTime() + 3600000;
    std::stringstream stream;
    stream << "current time: " << current;
    utils::Logger::log(stream.str());
  }
}

void OperationState::exitAction() {
  // stop application
}

bool OperationState::handleEvent(const EventPtr &event) {
  return false;
}

}