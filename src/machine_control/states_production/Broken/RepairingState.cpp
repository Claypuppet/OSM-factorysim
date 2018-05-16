
#include "RepairingState.h"

#include <utils/Logger.h>

#include "../Inititalization/ConfigureState.h"

namespace productionstates {

RepairingState::RepairingState(machinecore::Application &aContext)
: ProductionState(aContext) {
}

void RepairingState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);

}

void RepairingState::doActivity() {

}

void RepairingState::exitAction() {

}

bool RepairingState::handleEvent(const EventPtr &event) {
  switch(event->getId()) {
    case kEventTypeRepairFinished:
      onRepairFinishedEvent();
      return true;

    default:
      ProductionState::handleEvent(event);
  }
}

void RepairingState::onRepairFinishedEvent() {
  utils::Logger::log("-Handle event: kEventTypeRepairFinished");

  auto configureState = std::make_shared<ConfigureState>(context);
  context.setCurrentState(configureState);
}

}