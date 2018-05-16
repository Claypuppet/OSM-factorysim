
#include "IdleState.h"

#include <utils/Logger.h>

#include "../Inititalization/ConfigureState.h"

namespace productionstates {

IdleState::IdleState(machinecore::Application &aContext)
  :ProductionState(aContext) {
}

void IdleState::entryAction() {

}

void IdleState::doActivity() {

}

void IdleState::exitAction() {

}

bool IdleState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeReceivedConfig:
      onReceivedConfigEvent();
      return true;

    default:
      return ProductionState::handleEvent(event);
  }
}

void IdleState::onReceivedConfigEvent() {
  utils::Logger::log("-Handle event: kEventTypeReceivedConfig");
  context.setCurrentState(std::make_shared<ConfigureState>(context));
}

}