//
// Created by sven on 22-4-18.
//

#include "SimulationController.h"
#include "States/LoadConfigState.h"

Core::SimulationController::SimulationController() {
    setCurrentState(std::make_shared<States::LoadConfigState>());
}
