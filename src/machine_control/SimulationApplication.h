//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H

#include "Application.h"

namespace Simulator {
    class SimulationApplication : public MachineCore::Application {
    public:
        SimulationApplication(const Models::Machine& aMachineInfo);
        virtual ~SimulationApplication() = default;
    };
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H
