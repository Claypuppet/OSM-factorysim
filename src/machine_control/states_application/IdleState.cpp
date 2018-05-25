
#include "IdleState.h"

#include <utils/Logger.h>

#include "InOperationState.h"
#include "ConfigureState.h"

namespace applicationstates {

IdleState::IdleState(machinecore::Application &aContext)
    : ApplicationState(aContext) {
}

void IdleState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
//  context.statusUpdate(models::Machine::kMachineStatusIdle);
}

void IdleState::doActivity() {

}

void IdleState::exitAction() {

}

bool IdleState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeReceivedConfig: {
      onReceivedConfigEvent(event);
      return true;
    }

    case kEventTypeStartProcessing: {
      onStartProcessing();
      return true;
    }

    default: {
      return ApplicationState::handleEvent(event);
    }
  }
}

void IdleState::onReceivedConfigEvent(const EventPtr &event) {
  utils::Logger::log("-Handle event: kEventTypeReceivedConfig");

  context.setConfigToSet(event->getArgumentAsType<uint16_t>());

  auto state = std::make_shared<ConfigureState>(context);
  context.setCurrentState(state);
}

void IdleState::onStartProcessing() {
  utils::Logger::log("-Handle event: kEventTypeTakeProduct");

  auto state = std::make_shared<InOperationState>(context);
  context.setCurrentState(state);
}
} // applicationstates