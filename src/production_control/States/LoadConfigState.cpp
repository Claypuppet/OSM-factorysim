//
// Created by don on 24-4-18.
//

#include "LoadConfigState.h"
#include "../ConfigurationReader.h"
#include <iostream>
#include <Logger/Logger.h>

bool States::LoadConfigState::handleEvent(const Patterns::Statemachine::EventPtr &e) {
    return false;
}

void States::LoadConfigState::entryAction() {

}

void States::LoadConfigState::doActivity() {
    ConfigLoader::ConfigurationReader reader;
    Models::Configuration model;
    reader.readConfigurationFile("../configs/configfile.yaml", model);

    Models::ProductionLine productionline = model.getProductionLineConfiguration();
    Models::SimulationInfo simInfo = model.getSimulationInfoConfiguration();

    std::vector<Models::Machine> machines = productionline.getMachines();
    for(Models::Machine m : machines)
    {
        //Add to SimulationController and Application
    }

    while(1 == 1 /* Not done adding machines */)
    {

    }

    // Switch state to InitSimulationState
}

void States::LoadConfigState::exitAction() {

}
