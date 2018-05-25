
#include "SimulationMachine.h"
#include "states_machine/Configure/PrepareConfiguration.h"
#include "states_machine/InOperation/TakeProductState.h"

namespace simulator {

bool SimulationMachine::configure() {
  auto event = std::make_shared<machinestates::Event>(machinestates::kEventTypeConfigured);
  scheduleEvent(event);
  return true;
}

void SimulationMachine::selfTest() {
  auto event = std::make_shared<patterns::statemachine::Event>(machinestates::kEventTypeSelfTestSuccess);
  scheduleEvent(event);
}

void SimulationMachine::takeInProduct() {
  auto event = std::make_shared<machinestates::Event>(machinestates::kEventTypeProcessProduct);
  scheduleEvent(event);
}

void SimulationMachine::processProduct() {
  auto event = std::make_shared<machinestates::Event>(machinestates::kEventTypeFinishedProduct);
  scheduleEvent(event);
}

void SimulationMachine::takeOutProduct() {
  auto event = std::make_shared<machinestates::Event>(machinestates::kEventTypeProductTakenOut);
  scheduleEvent(event);
}

void SimulationMachine::setConfigureStartState() {
  auto state = std::make_shared<machinestates::PrepareConfiguration>(*this);
  setCurrentState(state);
}

void SimulationMachine::setInOperationStartState() {
  auto state = std::make_shared<machinestates::TakeProductState>(*this);
  setCurrentState(state);
}
} // simulator