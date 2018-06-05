//
// Created by klei on 6/5/18.
//

#include <utils/time/Time.h>

#include "SimulationMachinePostProcess.h"
#include "states_machine/MachineState.h"
#include "Application.h"

namespace simulator {

SimulationMachinePostProcess::SimulationMachinePostProcess(const models::Machine &machine) : SimulationMachine(machine) {

}

bool SimulationMachinePostProcess::configure() {
  return SimulationMachine::configure();
}

void SimulationMachinePostProcess::processProduct() {
  SimulationMachine::processProduct();
}

void SimulationMachinePostProcess::takeOutProduct() {
  performPostProcess();
  auto event = std::make_shared<machinestates::Event>(machinestates::kEventTypeProductTakenOut);
  scheduleEvent(event);
}

void SimulationMachinePostProcess::performPostProcess() {
  auto &time = utils::Time::getInstance();
  auto currentTime = time.getCurrentTime();
  uint64_t durationOfPostProcess = 1500000; // 25 min, todo: get from configuration

  time.increaseCurrentTime(durationOfPostProcess);
  auto notification = makeNotifcation(machinecore::NotifyEventType::kNotifyEventTypeProductAddedToBuffer);
  notifyObservers(notification);
  time.reset();
  time.syncTime(currentTime);
}

}