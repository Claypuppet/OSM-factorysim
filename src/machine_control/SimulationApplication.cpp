
#include <utils/time/Time.h>
#include "SimulationApplication.h"

#include "states_machine/MachineState.h"
#include "states_application/ConnectState.h"
#include "SimulationMachine.h"

namespace simulator {
SimulationApplication::SimulationApplication(uint16_t aMachineId)
    : Application(aMachineId) {
  machine = std::make_shared<SimulationMachine>();
  handleNotificationsFor(*machine);
}

void SimulationApplication::handleNotification(const patterns::notifyobserver::NotifyEvent &notification) {
  switch (notification.getEventId()) {
    case NotifyEventType::kNotifyEventTypeMachineConfigReceived : {
      auto event = std::make_shared<applicationstates::Event>(applicationstates::EventType::kEventTypeReceivedConfig);
      event->setArgument<uint32_t>(notification.getArgumentAsType<uint32_t>(0));
      scheduleEvent(event);
      break;
    }

    default: {
      Application::handleNotification(notification);
    }
  }
}

void SimulationApplication::setStartState() {
  setCurrentState(std::make_shared<applicationstates::ConnectState>(*this));
}
} // simulator