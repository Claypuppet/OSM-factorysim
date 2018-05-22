
#include "IdleState.h"

#include <utils/Logger.h>

#include "../Inititalization/ConfigureState.h"
#include "ProcessProduct/TakeProductState.h"

namespace productionstates {

IdleState::IdleState(machinecore::Application &aContext)
    : InOperationState(aContext) {
}

void IdleState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.statusUpdate(models::Machine::kMachineStatusIdle);
}

void IdleState::doActivity() {

}

void IdleState::exitAction() {

}

bool IdleState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeReceivedConfig:onReceivedConfigEvent(event);
      return true;

    case kEventTypeTakeProduct:onTakeProductEvent();
      return true;

    default:return ProductionState::handleEvent(event);
  }
}

void IdleState::onReceivedConfigEvent(const EventPtr &event) {
  utils::Logger::log("-Handle event: kEventTypeReceivedConfig");

  if (context.setCurrentConfigId(event->getArgumentAsType<uint32_t>())) {
    context.setCurrentState(std::make_shared<ConfigureState>(context));
  }
}

void IdleState::onTakeProductEvent() {
  utils::Logger::log("-Handle event: kEventTypeTakeProduct");

  auto takeProductState = std::make_shared<TakeProductState>(context);
  context.setCurrentState(takeProductState);
}

}