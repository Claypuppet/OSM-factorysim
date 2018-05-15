#include "InitializeSimulationState.h"
#include "OffState.h"
#include "models/Configuration.h"

namespace simulationstates {
void InitializeSimulationState::entryAction() {
  context.registerMachine();
}

void InitializeSimulationState::doActivity() {
}

void InitializeSimulationState::exitAction() {

}

bool InitializeSimulationState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeSimulationConfigurationsReceived: {
      onSimulationConfigurationsReceived(event);
      return true;
    }
    default: return SimulationState::handleEvent(event);
  }
}

void InitializeSimulationState::onSimulationConfigurationsReceived(const simulationstates::EventPtr &event) {
  context.setSimulationConfigurations(event->getArgumentAsType<std::vector<models::MachineConfiguration>>());
  context.setCurrentState(std::make_shared<OffState>(context));
}
}
