
#include <utils/Logger.h>

#include "SelfTestState.h"
#include "../../NotificationEventTypes.h"

namespace machinestates {

SelfTestState::SelfTestState(machinecore::Machine &aContext) :
	MachineState(aContext) {
}

void SelfTestState::entryAction() {
//  utils::Logger::log(__PRETTY_FUNCTION__);
}

void SelfTestState::doActivity() {
  if(!context.checkBroken()){
    context.selfTest();
  }
}

void SelfTestState::exitAction() {

}

bool SelfTestState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
	case kEventTypeSelfTestSuccess: {
      onSelfTestSuccess();
      return true;
    }

	case kEventTypeSelfTestFailed: {
      onSelfTestFail();
      return true;
    }

	default: {
      return MachineState::handleEvent(event);
    }
  }
}

void SelfTestState::onSelfTestSuccess() {
//  utils::Logger::log("-Handle event: kEventTypeSelfTestSuccess");

  auto event = patterns::notifyobserver::NotifyEvent(machinecore::kNotifyEventTypeMachineConfigured);
  context.notifyObservers(event);
}

void SelfTestState::onSelfTestFail() {
  utils::Logger::log("-Handle event: kEventTypeSelfTestFailed");

  auto event = patterns::notifyobserver::NotifyEvent(machinecore::kNotifyEventTypeMachineFailedToConfigure);
  context.notifyObservers(event);
}
} // machinestates