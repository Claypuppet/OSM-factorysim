//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H

#include "Application.h"

namespace simulator {
    class SimulationApplication : public MachineCore::Application {
    public:
        SimulationApplication(const models::Machine& aMachineInfo);
        virtual ~SimulationApplication() = default;
    };
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONAPPLICATION_H
