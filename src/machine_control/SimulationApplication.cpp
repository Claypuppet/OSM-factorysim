
#include "SimulationApplication.h"

#include "states_application/ProductionState.h"
#include "states_application/ConnectState.h"

namespace simulator {
SimulationApplication::SimulationApplication(uint16_t aMachineId)
	: Application(aMachineId) {
  machine = std::make_shared<SimulationMachine>();
}

void SimulationApplication::executeSelfTest() {
  bool succeeded = true;

  if (succeeded) {
	auto event = std::make_shared<patterns::statemachine::Event>(productionstates::kEventTypeSelfTestSuccess);
	scheduleEvent(event);
  } else {
	auto event = std::make_shared<patterns::statemachine::Event>(productionstates::kEventTypeSelfTestFailed);
	scheduleEvent(event);
  }
}
void SimulationApplication::setStartState() {
  setCurrentState(std::make_shared<productionstates::ConnectState>(*this));
}

}