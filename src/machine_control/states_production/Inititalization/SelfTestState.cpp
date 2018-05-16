
#include "SelfTestState.h"

#include <utils/Logger.h>

#include "../InOperation/IdleState.h"
#include "../Broken/BrokenState.h"

namespace productionstates {

SelfTestState::SelfTestState(machinecore::Application &aContext) :
    ProductionState(aContext) {
}

void SelfTestState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);

}

void SelfTestState::doActivity() {
  bool selfTestSucceeded = executeSelfTest();

  if (selfTestSucceeded) {
    auto event = std::make_shared<Event>(kEventTypeSelfTestSuccess);
    context.scheduleEvent(event);
  } else {
    auto event = std::make_shared<Event>(kEventTypeSelfTestFailed);
    context.scheduleEvent(event);
  }
}

void SelfTestState::exitAction() {

}

bool SelfTestState::handleEvent(const EventPtr &event) {
  switch(event->getId()) {
    case kEventTypeSelfTestSuccess:
      onSelfTestSuccess();
      return true;

    case kEventTypeSelfTestFailed:
      onSelfTestFail();
      return true;

    default:
      return ProductionState::handleEvent(event);
  }
}

bool SelfTestState::executeSelfTest() {
  return true; // for the current sprint goal the machine selftest only succeeds
}

void SelfTestState::onSelfTestSuccess() {
  utils::Logger::log("-Handle event: kEventTypeSelfTestSuccess");
  context.setCurrentState(std::make_shared<IdleState>(context));
}

void SelfTestState::onSelfTestFail() {
  utils::Logger::log("-Handle event: kEventTypeSelfTestFailed");

  // if a self test fails, that means that a machine is broken.
  context.setCurrentState(std::make_shared<BrokenState>(context));
}

}