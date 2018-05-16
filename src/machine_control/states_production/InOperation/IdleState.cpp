
#include "IdleState.h"

#include <utils/Logger.h>

#include "../Inititalization/ConfigureState.h"
#include "ProcessProduct/TakeProductState.h"

namespace productionstates {

IdleState::IdleState(machinecore::Application &aContext)
    : InOperationState(aContext) {
}

void IdleState::entryAction() {

}

void IdleState::doActivity() {

}

void IdleState::exitAction() {

}

bool IdleState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeReceivedConfig:onReceivedConfigEvent();
      return true;

    case kEventTypeTakeProduct:onTakeProductEvent();
      return true;

    default:return ProductionState::handleEvent(event);
  }
}

void IdleState::onReceivedConfigEvent() {
  utils::Logger::log("-Handle event: kEventTypeReceivedConfig");

  auto configureState = std::make_shared<ConfigureState>(context);
  context.setCurrentState(configureState);
}

void IdleState::onTakeProductEvent() {
  utils::Logger::log("-Handle event: kEventTypeReceivedConfig");

  auto takeProductState = std::make_shared<TakeProductState>(context);
  context.setCurrentState(takeProductState);
}

}