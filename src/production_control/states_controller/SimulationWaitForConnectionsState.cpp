//
// Created by don on 24-4-18.
//

#include <network/Connection.h>
#include "SimulationWaitForConnectionsState.h"
#include "OperationState.h"


states::SimulationWaitForConnectionsState::SimulationWaitForConnectionsState(simulation::SimulationController &context) :
        ControllerState(context)
{
}

void states::SimulationWaitForConnectionsState::entryAction() {
    context.setupNetwork();
}

void states::SimulationWaitForConnectionsState::doActivity() {

}

void states::SimulationWaitForConnectionsState::exitAction() {
    context.turnOnSimulationMachines();
}

bool states::SimulationWaitForConnectionsState::handleEvent(const EventPtr &e) {
    switch (e->getId()){
        case kEventTypeMachineConnected:
            context.registerMachine(e->getArgumentAsType<uint16_t>(0), e->getArgumentAsType<Network::ConnectionPtr>(1));
            break;
        case kEventTypeAllMachinesConnected:
//            context.setCurrentState(std::make_shared<OperationState>(context));
            break;
        default:
            return ControllerState::handleEvent(e);
    }
}
