//
// Created by don on 24-4-18.
//

#include <iostream>
#include <utils/Logger.h>

#include "LoadConfigState.h"

#include "../ConfigurationReader.h"
#include "SimulationBroadcastState.h"
#include "OperationState.h"

namespace States {
    LoadConfigState::LoadConfigState(simulation::SimulationController &context) : ControllerState(context) {}


    bool LoadConfigState::handleEvent(const EventPtr &e) {
        switch (e->getId()){
            case kEventTypeReadConfigFile:
                // TODO: read config on context
                context.setConfigFromFile(e->getArgumentAsType<std::string>());
                break;
            case kEventTypeSimulationConfigLoaded:
                context.setCurrentState(std::make_shared<SimulationBroadcastState>(context));
                break;
            case kEventTypeProductionConfigLoaded:
                context.setCurrentState(std::make_shared<OperationState>(context));
                break;
            default:
                return ControllerState::handleEvent(e);
        }
    }
    
    void LoadConfigState::entryAction() {
    
    }
    
    void LoadConfigState::doActivity() {
    }
    
    void LoadConfigState::exitAction() {
    
    }

}