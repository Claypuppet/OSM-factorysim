#include "ProductionLineConfiguration.h"

ProductionLineConfiguration::ProductionLineConfiguration(const YAML::Node& productionLineConfigurationNode)
: name(productionLineConfigurationNode["name"].as<std::string>()) {

    for (uint16_t i = 0; i < productionLineConfigurationNode["products"].size(); ++i) {
        const YAML::Node& productNode = productionLineConfigurationNode["products"][i];
        products.push_back(ProductConfiguration(productNode));
    }

    for (uint16_t i = 0; i < productionLineConfigurationNode["machines"].size(); ++i) {
        const YAML::Node& machineNode = productionLineConfigurationNode["machines"][i];
        machines.push_back(MachineConfiguration(machineNode));
    }

}

ProductionLineConfiguration::ProductionLineConfiguration(const ProductionLineConfiguration& other)
: name(other.name),
  products(other.products),
  machines(other.machines) {
}

ProductionLineConfiguration::~ProductionLineConfiguration() {
}