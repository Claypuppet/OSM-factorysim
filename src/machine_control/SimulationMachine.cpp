
#include "SimulationMachine.h"
#include "states_machine/Configure/PrepareConfiguration.h"
#include "states_machine/InOperation/TakeProductState.h"

#include <utils/time/Time.h>

namespace simulator {

SimulationMachine::SimulationMachine() : Machine(), timeSinceBrokenCheck(0), checkCycle(3600000) {

}

bool SimulationMachine::configure() {
  distribution = std::uniform_int_distribution<uint64_t>(magicNumber,
                                                         (magicNumber
                                                             + currentConfiguration->getMeanTimeBetweenFailureInHours())
                                                             * 3600000/checkCycle);

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

bool SimulationMachine::checkBroken() {
  if (utils::Time::getInstance().getCurrentTime() + checkCycle > timeSinceBrokenCheck) {
    if (distribution(generator) == magicNumber) {
      return true;
    }
  }
  return false;
}
} // simulator