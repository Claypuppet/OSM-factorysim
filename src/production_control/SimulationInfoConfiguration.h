//
// Created by bas on 20-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H


#include <cstdint>

#include <yaml-cpp/node/node.h>

class SimulationInfoConfiguration {
public:
    SimulationInfoConfiguration(const YAML::Node& simulationInfoNode);
    SimulationInfoConfiguration(const SimulationInfoConfiguration& other);
    virtual ~SimulationInfoConfiguration();

private:
    uint8_t durationInHours;
};


#endif //PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H
