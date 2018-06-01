
#include <utils/time/Time.h>
#include "SimulationMachine.h"
#include "states_machine/Configure/PrepareConfiguration.h"
#include "states_machine/InOperation/TakeProductState.h"

#include <utils/time/Time.h>

namespace simulator {

const uint64_t oneHourInMillis = 3600000;

bool SimulationMachine::canBreak = true;
bool SimulationMachine::timeCycles = true;

SimulationMachine::SimulationMachine() : Machine(), timeSinceBrokenCheck(0), checkCycle(oneHourInMillis) {

}

bool SimulationMachine::configure() {
  distribution = std::uniform_int_distribution<uint64_t>(magicNumber,
                                                         (magicNumber
                                                             + currentConfiguration->getMeanTimeBetweenFailureInHours())
                                                             * 3600000 / checkCycle);
  utils::Time::getInstance().increaseCurrentTime(currentConfiguration->getInitializationDurationInMilliseconds());
  auto event = std::make_shared<machinestates::Event>(machinestates::kEventTypeConfigured);
  scheduleEvent(event);
  return true;
}

void SimulationMachine::selfTest() {
  auto event = std::make_shared<patterns::statemachine::Event>(machinestates::kEventTypeSelfTestSuccess);
  scheduleEvent(event);
}

void SimulationMachine::takeInProduct() {
  auto event = std::make_shared<machinestates::Event>(machinestates::kEventTypeProductTakenIn);
  scheduleEvent(event);
}

void SimulationMachine::processProduct() {
  uint32_t processTime = currentConfiguration ? currentConfiguration->getProcessTime() : 0;
  utils::Time::getInstance().increaseCurrentTime(processTime);
  auto event = std::make_shared<machinestates::Event>(machinestates::kEventTypeProductProcessed);
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
  if (canBreak) {
    if (timeCycles) {
      auto currentTime = utils::Time::getInstance().getCurrentTime();
      if (currentTime < timeSinceBrokenCheck + checkCycle) {
        return false;
      }
    }
    timeSinceBrokenCheck = utils::Time::getInstance().getCurrentTime();
    uint64_t generated = distribution(generator);
    generated = distribution(generator);
    if (generated == magicNumber) {
      auto stateEvent = std::make_shared<machinestates::Event>(machinestates::kEventTypeMachineBroke);
      scheduleEvent(stateEvent);
      return true;
    }
  }
  return false;
}

/* static */ void SimulationMachine::setCanBreak(bool canBreak) {
  SimulationMachine::canBreak = canBreak;
}

/* static */ void SimulationMachine::setTimeCycles(bool timeCycles) {
  SimulationMachine::timeCycles = timeCycles;
}
} // simulator