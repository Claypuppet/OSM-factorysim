
#include "InOperationState.h"
#include "WaitForConnectionsState.h"
#include "in_operation/PrepareShutdownState.h"

#include <utils/Logger.h>

namespace applicationstates {

InOperationState::InOperationState(core::Application &context) : ApplicationState(context) {
}

void InOperationState::doActivity() {
  context.executeScheduler();
  std::this_thread::yield();
}

bool applicationstates::InOperationState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case applicationstates::kEventTypeMachineStatusUpdate:
      onMachineStatusUpdateEvent(event);
      return true;
    case applicationstates::kEventTypeMachineProductTakenFromBuffer:
      onMachineProductTaken(event);
      return true;
    case applicationstates::kEventTypeMachineProductAddedToBuffer:
      onMachineProductAdded(event);
      return true;
    case applicationstates::kEventTypeMachineDisconnected:
      onMachineDisconnected(event);
      return true;
    case applicationstates::kEventTypeWorkDayOver:
      onWorkDayOver();
      return true;
    default: {
      return ApplicationState::handleEvent(event);
    }
  }
}

void InOperationState::onMachineStatusUpdateEvent(const EventPtr &event) {
//	utils::Logger::log("-Handle event: kEventTypeMachineStatusUpdate");
  context.setMachineStatus(event->getArgumentAsType<uint16_t>(0),
                           event->getArgumentAsType<core::Machine::MachineStatus>(1));
}

void applicationstates::InOperationState::onMachineProductTaken(const applicationstates::EventPtr &event) {
  context.takeProductsFromBuffer(event->getArgumentAsType<uint16_t>(0));
}

void applicationstates::InOperationState::onMachineProductAdded(const applicationstates::EventPtr &event) {
  context.addProductsToBuffer(event->getArgumentAsType<uint16_t>(0));
}

void applicationstates::InOperationState::onMachineDisconnected(const applicationstates::EventPtr &event) {
  // A machine disconnected mid production? wait for machine again...
  context.setCurrentState(std::make_shared<WaitForConnectionsState>(context));
}

void applicationstates::InOperationState::onWorkDayOver() {
  context.setCurrentState(std::make_shared<PrepareShutdownState>(context));
}

}
