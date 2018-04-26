//
// Created by don on 24-4-18.
//

#include "SimulationWaitForConnectionsState.h"
#include "OperationState.h"


void States::SimulationWaitForConnectionsState::entryAction() {
    context.setupNetwork();
}

void States::SimulationWaitForConnectionsState::doActivity() {

}

void States::SimulationWaitForConnectionsState::exitAction() {
    context.turnOnSimulationMachines();
}

bool States::SimulationWaitForConnectionsState::handleEvent(const EventPtr &e) {
    switch (e->getId()){
        case kEventTypeMachineConnected:
            context.setConfigFromFile(e->getArgumentAsType<std::string>());
            break;
        case kEventTypeAllMachinesConnected:
//            context.setCurrentState(std::make_shared<OperationState>(context));
            break;
        default:
            return ControllerState::handleEvent(e);
    }
}
