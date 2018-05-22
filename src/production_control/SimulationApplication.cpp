//
// Created by klei on 5/16/18.
//

#include "SimulationApplication.h"
#include "states_application/WaitForConnectionsState.h"

namespace simulation {

void SimulationApplication::turnOnSimulationMachines() {
  for (const auto &machine : machines) {
    auto simMachine = std::dynamic_pointer_cast<SimulationMachine>(machine);
    if(simMachine){
      simMachine->sendTurnOnCommand();
    }
  }
}

void SimulationApplication::turnOffSimulationMachines() {
  for (const auto &machine : machines) {
    auto simMachine = std::dynamic_pointer_cast<SimulationMachine>(machine);
    if(simMachine){
      simMachine->sendTurnOnCommand();
    }
  }
}

void SimulationApplication::setupNetwork() {
  Application::setupNetwork();
  turnOnSimulationMachines();
}

}