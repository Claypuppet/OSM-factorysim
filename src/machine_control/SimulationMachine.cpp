#include <ctime>
#include <utils/time/Time.h>
#include "SimulationMachine.h"
#include "states_machine/Configure/PrepareConfiguration.h"
#include "states_machine/InOperation/TakeProductState.h"
#include "Application.h"

#include <utils/time/Time.h>

namespace simulator {

const uint64_t oneMinuteInMillis = 60000;
const uint64_t oneHourInMillis = oneMinuteInMillis * 60;

bool SimulationMachine::canBreak = true;

SimulationMachine::SimulationMachine(const models::Machine &machine) : machinecore::Machine(machine), timeSinceBrokenCheck(0), checkCycle(oneMinuteInMillis) {

}

bool SimulationMachine::configure() {
  generator = std::mt19937(static_cast<uint64_t >(std::clock()));
  distribution = std::uniform_int_distribution<uint64_t>(magicNumber,
                                                         (magicNumber
                                                             + currentConfiguration->getMeanTimeBetweenFailureInHours())
                                                             * oneHourInMillis / checkCycle);
  utils::Time::getInstance().increaseCurrentTime(currentConfiguration->getInitializationDurationInMilliseconds());
  timeSinceBrokenCheck = utils::Time::getInstance().getCurrentTime();
  auto event = std::make_shared<machinestates::Event>(machinestates::kEventTypeConfigured);
  scheduleEvent(event);
  return true;
}

void SimulationMachine::selfTest() {
  auto event = std::make_shared<patterns::statemachine::Event>(machinestates::kEventTypeSelfTestSuccess);
  scheduleEvent(event);
}

void SimulationMachine::takeInProduct() {
  auto notification = makeNotifcation(machinecore::NotifyEventType::kNotifyEventTypeProductTakenFromBuffer);
  notifyObservers(notification);
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
  auto notification = makeNotifcation(machinecore::NotifyEventType::kNotifyEventTypeProductAddedToBuffer);
  notifyObservers(notification);
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
    auto currentTime = utils::Time::getInstance().getCurrentTime();
    if (currentTime < timeSinceBrokenCheck + checkCycle) {
      return false;
    }

    while(currentTime > timeSinceBrokenCheck){
      // Catch up with history
      timeSinceBrokenCheck += checkCycle;

      uint64_t generated = distribution(generator);

      if (generated == magicNumber) {
        // It broke, set time since last check to now
        timeSinceBrokenCheck = currentTime;
        auto stateEvent = std::make_shared<machinestates::Event>(machinestates::kEventTypeMachineBroke);
        scheduleEvent(stateEvent);
        return true;
      }
    }
  }
  return false;
}

/* static */ void SimulationMachine::setCanBreak(bool canBreak) {
  SimulationMachine::canBreak = canBreak;
}
} // simulator