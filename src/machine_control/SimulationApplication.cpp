
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

void SimulationApplication::takeProductIn() {
    // TODO : take product from machine
}

void SimulationApplication::processProduct() {
    // TODO : proccess the taken product
}


void SimulationApplication::takeProductOut() {
    // TODO : Take the product out of the machine and into the output buffer
}

}