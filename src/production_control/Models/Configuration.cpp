#include "Configuration.h"

namespace models {

    Configuration::Configuration() {
    }

    Configuration::Configuration(const Configuration &other)
            : name(other.name),
              simulationInfoConfiguration(other.simulationInfoConfiguration),
              productionLineConfiguration(other.productionLineConfiguration) {
    }

    Configuration::~Configuration() {
    }

    void Configuration::deserialize(YAML::Node &configurationNode) {
        name = configurationNode["name"].as<std::string>();

        auto simulationInfoNode = configurationNode["simulationInfo"];
        simulationInfoConfiguration.deserialize(simulationInfoNode);

        auto productionLineNode = configurationNode["productionLine"];
        productionLineConfiguration.deserialize(productionLineNode);
    }

    const std::string &Configuration::getName() const {
        return name;
    }

    const SimulationInfoConfiguration &Configuration::getSimulationInfoConfiguration() const {
        return simulationInfoConfiguration;
    }

    const ProductionLineConfiguration &Configuration::getProductionLineConfiguration() const {
        return productionLineConfiguration;
    }

}
