//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H

#include <network/Manager.h>
#include "SimulationNetworkComponent.h"
#include "Controller.h"
#include "SimulationApplication.h"

namespace Simulator {

    class SimulationController : public Core::Controller, public Patterns::Statemachine::Context   {
    public:
        SimulationController();
        virtual ~SimulationController() = default;

    private:
        Network::ClientPtr client;
    };
}


#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
