//
// Created by don on 24-4-18.
//

#include <network/Connection.h>
#include "SimulationWaitForConnectionsState.h"
#include "OperationState.h"


States::SimulationWaitForConnectionsState::SimulationWaitForConnectionsState(Simulation::SimulationController &context) :
        ControllerState(context)
{
}

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
            context.registerMachine(e->getArgumentAsType<uint16_t>(0), e->getArgumentAsType<Network::ConnectionPtr>(1));
            break;
        case kEventTypeAllMachinesConnected:
//            context.setCurrentState(std::make_shared<OperationState>(context));
            break;
        default:
            return ControllerState::handleEvent(e);
    }
}
