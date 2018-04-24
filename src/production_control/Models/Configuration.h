#ifndef PRODUCTION_LINE_CONTROL_CONFIG_H
#define PRODUCTION_LINE_CONTROL_CONFIG_H

#include <string>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

#include "SimulationInfoConfiguration.h"
#include "ProductionLineConfiguration.h"

namespace models {

    class Configuration {
    public:
        Configuration();

        Configuration(const Configuration &other);

        virtual ~Configuration();

        void deserialize(YAML::Node &configurationNode);

        const std::string &getName() const;

        const SimulationInfoConfiguration &getSimulationInfoConfiguration() const;

        const ProductionLineConfiguration &getProductionLineConfiguration() const;

    private:
        std::string name;
        SimulationInfoConfiguration simulationInfoConfiguration;
        ProductionLineConfiguration productionLineConfiguration;
    };

}

#endif //PRODUCTION_LINE_CONTROL_CONFIG_H
