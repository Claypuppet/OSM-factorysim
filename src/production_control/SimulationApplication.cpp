//
// Created by klei on 5/16/18.
//

#include "SimulationApplication.h"
#include "states_application/WaitForConnectionsState.h"

namespace simulation {

void SimulationApplication::turnOnSimulationMachines() {
  for (const auto &machine : machines) {
	machine->sendTurnOnCommand();
  }
}

void SimulationApplication::turnOffSimulationMachines() {
  for (const auto &machine : machines) {
	machine->sendTurnOffCommand();
  }
}
void SimulationApplication::setupNetwork() {
  Application::setupNetwork();
  turnOnSimulationMachines();
}
void SimulationApplication::setMachines(const std::vector<SimulationMachinePtr> &aMachines) {
  std::vector<core::MachinePtr> coreMachines;
  for (const auto&machine : aMachines){
    coreMachines.emplace_back(machine);
  }
  core::Application::setMachines(coreMachines);
  machines = aMachines;
}

}