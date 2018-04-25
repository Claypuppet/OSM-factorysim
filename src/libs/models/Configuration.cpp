#include "Configuration.h"

namespace Models {

    Configuration::Configuration() {
    }

    Configuration::Configuration(const Configuration &other)
            : name(other.name),
              simulationInfoConfiguration(other.simulationInfoConfiguration),
              productionLineConfiguration(other.productionLineConfiguration) {
    }

    Configuration::~Configuration() {
    }

    Configuration& Configuration::operator=(const Configuration &other) {
        if (this != &other) {
            this->name = other.name;
            this->simulationInfoConfiguration = other.simulationInfoConfiguration;
            this->productionLineConfiguration = other.productionLineConfiguration;
        }

        return *this;
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

    const SimulationInfo &Configuration::getSimulationInfoConfiguration() const {
        return simulationInfoConfiguration;
    }

    const ProductionLine &Configuration::getProductionLineConfiguration() const {
        return productionLineConfiguration;
    }

}
