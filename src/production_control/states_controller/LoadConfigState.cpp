//
// Created by don on 24-4-18.
//

#include "LoadConfigState.h"
#include "../ConfigurationReader.h"
#include "SimulationBroadcastState.h"
#include "BroadCastState.h"
#include <iostream>
#include <Logger/Logger.h>

bool States::LoadConfigState::handleEvent(const EventPtr &e) {
    switch (e->getId()){
        case kEventTypeReadConfigFile:
            // TODO: read config on context
            context.setConfigFromFile(e->getArgumentAsType<std::string>());
            break;
        case kEventTypeSimulationConfigLoaded:
            context.setCurrentState(std::make_shared<SimulationBroadcastState>(context));
            break;
        case kEventTypeProductionConfigLoaded:
            context.setCurrentState(std::make_shared<BroadCastState>(context));
            break;
        default:
            return ControllerState::handleEvent(e);
    }
}

void States::LoadConfigState::entryAction() {

}

void States::LoadConfigState::doActivity() {
}

void States::LoadConfigState::exitAction() {

}
