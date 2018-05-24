
#include "SimulationMachine.h"
#include "states_machine/Configure/ReadyingConfigState.h"
#include "states_machine/InOperation/TakeProductState.h"

namespace simulator {

bool SimulationMachine::configure() {
  return true;
}

void SimulationMachine::selfTest() {
  bool succeeded = true;

  if (succeeded) {
    auto event = std::make_shared<patterns::statemachine::Event>(machinestates::kEventTypeSelfTestSuccess);
    scheduleEvent(event);
  } else {
    auto event = std::make_shared<patterns::statemachine::Event>(machinestates::kEventTypeSelfTestFailed);
    scheduleEvent(event);
  }
}

void SimulationMachine::takeInProduct() {

}

void SimulationMachine::processProduct() {

}

void SimulationMachine::takeOutProduct() {

}

void SimulationMachine::setConfigureStartState() {
  auto state = std::make_shared<machinestates::ReadyingConfigState>(*this);
  setCurrentState(state);
}

void SimulationMachine::setInOperationStartState() {
  auto state = std::make_shared<machinestates::TakeProductState>(*this);
  setCurrentState(state);
}
} // simulator