//
// Created by don on 24-4-18.
//

#include "LoadConfigState.h"
#include "../ConfigurationReader.h"
#include <iostream>

bool LoadConfigState::handleEvent(const Patterns::Statemachine::Event &e, Patterns::Statemachine::Context &c) {
    return false;
}

void LoadConfigState::entryAction() {

}

void LoadConfigState::doActivity() {
    ConfigurationReader reader;
    Models::Configuration model;;
    reader.readConfigurationFile("path/to/config/file", model);

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

void LoadConfigState::exitAction() {

}
