//
// Created by don on 24-4-18.
//

#include "WaitForConnectionsState.h"


ApplicationStates::WaitForConnectionsState::WaitForConnectionsState(core::Application &context) :
        ApplicationState(context)
{
}

/**
 * Waits untill all configured machines are connected to the SimulationControll component
 * Sends simulation configuration to all connected machines
 */
void ApplicationStates::WaitForConnectionsState::doActivity() {

}

void ApplicationStates::WaitForConnectionsState::entryAction() {

}

void ApplicationStates::WaitForConnectionsState::exitAction() {

}

bool ApplicationStates::WaitForConnectionsState::handleEvent(const EventPtr &event) {
    switch (event->getId()){
        case kEventTypeMachineConnected:
            context.registerMachine(event->getArgumentAsType<uint16_t>(0), event->getArgumentAsType<Network::ConnectionPtr>(1));
        break;
        case kEventTypeAllMachinesConnected:
            context.setCurrentState(std::make_shared<OperationState>(context));
            break;
        default:
            return ApplicationState::handleEvent(event);
    }
}
