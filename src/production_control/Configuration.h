#ifndef PRODUCTION_LINE_CONTROL_CONFIG_H
#define PRODUCTION_LINE_CONTROL_CONFIG_H

#include <string>

#include <yaml-cpp/node/node.h>

#include "SimulationInfoConfiguration.h"
#include "ProductionLineConfiguration.h"

class Configuration {
public:
    Configuration();
    Configuration(const YAML::Node& configurationNode);
    Configuration(const Configuration& other);
    virtual ~Configuration();

private:
    std::string name;
    SimulationInfoConfiguration simulationInfoConfiguration;
    ProductionLineConfiguration productionLineConfiguration;
};


#endif //PRODUCTION_LINE_CONTROL_CONFIG_H
