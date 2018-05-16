
#include "SimulationApplication.h"

#include "states_production/ProductionState.h"

namespace simulator {
SimulationApplication::SimulationApplication(uint16_t aMachineId)
    : Application(aMachineId), machine() {
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

}