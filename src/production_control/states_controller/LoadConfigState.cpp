//
// Created by don on 24-4-18.
//

#include "LoadConfigState.h"
#include "../ConfigurationReader.h"
#include "SimulationBroadcastState.h"
#include "BroadCastState.h"
#include <iostream>

bool States::LoadConfigState::handleEvent(const EventPtr &e) {
    switch (e->getId()){
        case kEventTypeReadConfigFile:
            // TODO: read config on context
            auto fileLocation = e->getArgumentAsType<std::string>();
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
    ConfigLoader::ConfigurationReader reader;
    Models::Configuration model;
    reader.readConfigurationFile("path/to/config/file", model);

    Models::ProductionLine productionline = model.getProductionLineConfiguration();
    Models::SimulationInfo simInfo = model.getSimulationInfoConfiguration();

    std::vector<Models::Machine> machines = productionline.getMachines();
    for(Models::Machine m : machines)
    {
        //Add to SimulationController and Application
    }
}

void States::LoadConfigState::exitAction() {

}
