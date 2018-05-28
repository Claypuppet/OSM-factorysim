
#include <utils/time/Time.h>
#include "SimulationApplication.h"

#include "states_machine/MachineState.h"
#include "states_application/ConnectState.h"
#include "SimulationMachine.h"

namespace simulator {
SimulationApplication::SimulationApplication(uint16_t aMachineId)
    : Application(aMachineId) {
  machine = std::make_shared<SimulationMachine>();
  handleNotificationsFor(*machine);
}

void SimulationApplication::setStartState() {
  setCurrentState(std::make_shared<applicationstates::ConnectState>(*this));
}
} // simulator